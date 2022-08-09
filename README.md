# GAS Lab
UE4 GAS 스터디 프로젝트.

- [Dan's Knowledge and Gameplay Example](https://github.com/tranek/GASDocumentation/)을 스터디하며 이해한 내용을 기록한 프로젝트.
- 개발 단계별로 별도 브랜치를 나누어 해당 단계에 필요한 내용만 볼 수 있도록 했음.
- GAS에 대한 세부 내용은 [UE4 문서](https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/GameplayAbilitySystem/) 및 [Dan's Knowledge and Gameplay Example](https://github.com/tranek/GASDocumentation/)를 참조 할 것.

# Step 1. 시스템 초기화

## 1.1 프로젝트 설정
1. 에디터에서 GameplayAbilitySystem 플러그인 활성화
2. `YourProjectName.Build.cs`에서 `PrivateDependencyModuleNames`에 다음 모듈들 추가
   - `"GameplayAbilities"`, `"GameplayTasks"`, `"GameplayTags"`
3. [TargetData](https://github.com/tranek/GASDocumentation/#concepts-targeting-data)를 사용하기 위해서는 `UAbilitySystem::Get().InitGlobalData()`를 반드시 호출해야 한다고 한다.  
   이 함수는 프로젝트 시작 시점에 한번만 호출하면 되며, Fortnite은 `UAssetManager::StartInitialLoading()`에서 Paragon은 `UEngine::Init()`에서 호출하고 있다고 하며, 이 프로젝트에서는 `UEngineSubsystem::Initialize()`에서 호출하도록 했다.
   추가로 `UGameInstance::Init()` 에서 호출하는 것도 괜찮은 것 같다. 
   세부 내용은 [`InitGlobalData()`](https://github.com/tranek/GASDocumentation/#concepts-asg-initglobaldata) 내용을 참조할 것.
   
   