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

PlayerState 에 `ASC`와 `Attribute` 인스턴스 생성을 했다. 아마 멀티플레이 환경에서 다른 플레이어의 `Attribute` 참조를 위해 PlayerState를 선택한 것으로 생각된다.
`ASC` 컴포넌트의 Own 액터는 반드시 `IAbilitySystemInterface`를 상속해야 하며, 컴포넌트 초기화 과정에서 Owner 클래스에 인스턴싱된 `UAttribteSet` 클래스 인스턴스를 검색하여
자동으로 컴포넌트에 링크하고 있다.
때문에 `Attribute`의 인스턴스 생성은 컴포넌트 초기화 전이어야 하므로 `생성자`가 가장 무난하며 특수한 이유로 동적으로 생성해야 한다면 `PostInitializeComponent()`에서 생성하면 된다.



