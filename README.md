# GAS Lab

UE4 GAS 스터디 프로젝트.

- [Dan's Knowledge and Gameplay Example](https://github.com/tranek/GASDocumentation/)을 스터디하며 이해한 내용을 기록한 프로젝트.
- 개발 단계별로 별도 브랜치를 나누어 해당 단계에 필요한 내용만 볼 수 있도록 했음.
- GAS에 대한 세부 내용은 [UE4 문서](https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/GameplayAbilitySystem/)
  및 [Dan's Knowledge and Gameplay Example](https://github.com/tranek/GASDocumentation/)를 참조 할 것.

# Step 1. 시스템 초기화

## 1.1 프로젝트 설정

1. 에디터에서 GameplayAbilitySystem 플러그인 활성화
2. `YourProjectName.Build.cs`에서 `PrivateDependencyModuleNames`에 다음 모듈들 추가
    - `"GameplayAbilities"`, `"GameplayTasks"`, `"GameplayTags"`
3. [TargetData](https://github.com/tranek/GASDocumentation/#concepts-targeting-data)를 사용하기
   위해서는 `UAbilitySystem::Get().InitGlobalData()`를 반드시 호출해야 한다고 한다.  
   이 함수는 프로젝트 시작 시점에 한번만 호출하면 되며, Fortnite은 `UAssetManager::StartInitialLoading()`에서, Paragon은 `UEngine::Init()`에서 호출하고
   있다고 한다.
   이 프로젝트에서는 `UEngineSubsystem::Initialize()`에서 호출하도록 했지만 `UGameInstance::Init()` 에서 호출하는 것도 괜찮은 것 같다.
   세부 내용은 [`InitGlobalData()`](https://github.com/tranek/GASDocumentation/#concepts-asg-initglobaldata) 내용을 참조할 것.

## 1.2 `GAS` 시스템 초기화

### 1.2.1 [시스템 컨셉](https://github.com/tranek/GASDocumentation/#concepts-asc)

`GAS`는 `UAbilitySystemComponent(이하 ASC)`, `AttributeSet(이하 Attribute)`, `GameplayAbility(이하 GA)`
, `GameplayEffect(이하 GE)`로 구성된다.

- `Attribute`는 문서상 설명으로는 float로 표현 될 수 있는 데이터 집합을 의미하며, 흔히 캐릭터의 스탯 데이터 셋을 말한다.
- `GA`는 캐릭터의 행동 또는 능력을 의미하며 RPG 예를 들면 캐릭터의 스킬이 바로 `GA`가 된다.
- `GE`는 행위에 대한 효과로 `Attribute`를 계산하고 수정하는 역할을 담당한다.
- `ASC`는 `GA`를 실행하고 `GE`와 `Attribute`를 연겷하여 데이터 수정하는 모든 것을 책임지며, 멀티플레이에서의 리플리케이션 역시 책임진다.

정리하면 `GAS`는 캐릭터의 행위(`GA`)를 실행하고 그 결과인 `GE`를 통해 `Attribute`에 반영하는 시스템이다.

### 1.2.2 시스템 설정 및 초기화

`GAS`를 사용하는 캐릭터(주로 캐릭터이므로 이를 기준으로 설명)는 스탯 데이터를 가지고 있는 `AttributeSet`과 시스템을 구동하는 `ASC(AbilitySystemCommponent)` 인스턴스를 가지고 있어야 한다.
때문에 `AttributeSet`, `ASC` 인스턴스 생성 및 관리가 이번 단계에서 해야 할 목표이고, 이를 위해서 다음 사항을 결정해야 한다.

1. `AttributeSet` 인스턴스를 `ASC` 인스턴스에 연결
   - `ASC`가 데이터(`AttributeSet`)을 수정하기 위해서 당연히 `AttributeSet`의 인스턴스를 알고 있어야 한다.
   - 때문에 `ASC`는 컴포넌트 초기화 시점에 Owner가 갖고 있는 `AttributeSet` 인스턴스들을 검색하여 자동으로 캐싱하고 있다.
     - 샘플들이 생성자에서 `ASC`와 `AttributeSet`에서 인스턴스를 생성하는 이유가 바로 이 때문이다.
   - 하지만 어떤 이유로 생성자 이후에 `AttributeSet`을 생성해야 한다면 다음 두가지 방법을 검토해야 할 것이다.
     - `PostInitializeComponent()`에서 생성하면 생성자에서 `AttributeSet`을 생성하는 것과 동일한 효과를 얻을 수 있다.(즉, 자동으로 `ASC`가 검색하여 연결할 수 있다.)
     - `ASC` 초기화(InitilalizeComponent()) 이후에 생성한다면 UAbilitySystemComponent::GetOrCreateAttributeSubobject()를 사용하여 생성한다.

2. `AttributeSet`, `ASC` 인스턴스 소유자 결정
   - 두 인스턴스 모두 캐릭터의 현재 상태를 갖고 있으므로 인스턴스 수명에 대한 문제가 중요해지기도 한다.
     - 보통 싱글 플레이의 경우 단순하게 캐릭터에서 모두 처리해도 된다.
   - 변신 등의 이유로 캐릭터 인스턴스를 변경해야 하는 경우, 그리고 그게 멀티플레이 게임이라면 캐릭터가 아닌 다른 곳을 생각해야 한다.
     - 참고한 프로젝트의 경우 PlayerState를 소유자로 선택했다.
       - PlayerController 의 경우는 서버와 로컬 플레이어만 리플리케이션 되므로 다른 클라이언트에 대한 처리가 복잡해 질 수 있다.
       - PlayerState는 모든 클라이언트에 동기화되며 캐릭터에 PlayerState 리플리케이션 노티파이 이벤트까지 있으므로 쉽게 처리가 가능한 장점이 있다.

3. 인스턴스 소유자 결정에 따른 `ASC` 초기화 시퀀스 
    - `ASC`는 Owner와 Avatar 두개의 액터와 연결되어야 한다.
      - Owner는 일반적인 컴포넌트 소유 액터이다. `AttributeSet` 등의 인스턴스 참조부터 Replication relevant 문제까지 일반적인 Owner의 역할을 한다.
      - Avatar는 `ASC`에 영향받을 Pawn 이다. 애니메이션, 이펙트 플레이 같은 효과부터 `AttributeSet` 데이터 변화의 효과를 모두 표현할 액터이다.
    - 때문에 캐릭터 변경시 반드시 `UAbilitySystemComponent::InitAbilityActorInfo()`를 호출하여 Owner와 Avatar 액터 링크를 업데이트 해야 한다.
      - 모든 클라이언트가 이 함수를 호출해야 하므로 멀티플레이 환경에서 캐릭터가 아닌 PlayerState 또는 PlayerController 가 소유자인 경우 서버/클라이언트 별로 호출 시점이 나뉘게 된다.
    
결론은 시스템 구성과 초기화 방식은 크게 두가지 방법이 있고, 이 프로젝트에서는 이 두 방법을 모두 보여주기 위해 플레이어와 AI 캐릭터를 각각 다르게 구현했다.
1. 플레이어
    - PlayerState에서 `ASC` 및 `AttributeSet` 인스턴스를 생성하고 관리한다.
    - 플레이어 캐릭터는 서버와 클라이언트가 각가 다른 시점에 시스템 초기화를 실행한다.
      - 서버 (`OnPossess()`) : PlayerState를 참조해야 하므로 컨트롤러가 연결되는 시점에서 초기화를 실행한다.
      - 클라이언트 (`OnRep_PlayerState()`) : PlayerState 인스턴스가 리플리케이션 되는 시점에서 초기화를 실행한다.
2. AI 캐릭터
   - AI 캐릭터는 캐릭터가 `ASC` 및 `AttributeSet` 인스턴스를 생성하고 관리한다.
   - 때문에 서버, 클라이언트 모두 BeginPlay()에서 시스템 초기화를 실행한다.

