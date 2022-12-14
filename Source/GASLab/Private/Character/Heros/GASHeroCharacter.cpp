// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Heros/GASHeroCharacter.h"
#include "AbilitySystem/GASAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/GASCharacterAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/GASPlayerController.h"
#include "Player/GASPlayerState.h"
#include "AI/GASAIController.h"
#include "Kismet/KismetMathLibrary.h"


AGASHeroCharacter::AGASHeroCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0, 0, 68.492264));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->SetFieldOfView(80.0f);

	GunComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AIControllerClass = AGASAIController::StaticClass();
}

void AGASHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGASHeroCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGASHeroCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AGASHeroCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGASHeroCharacter::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &AGASHeroCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGASHeroCharacter::TurnRate);

	BindASCInput();
}

void AGASHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// [??????] ASC ?????????
	AGASPlayerState* PS = GetPlayerState<AGASPlayerState>();
	if(PS)
	{
		// ASC ???????????? ?????? ??? ActorInfo ?????????
		AbilitySystemComponent = Cast<UGASAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		// AttributeSet ???????????? ?????? ??? ?????????
		AttributeSet = PS->GetAttributeSet();
		InitializeAttributes();

		// ????????? ???????????? ????????? ?????????
		// TODO: State.Dead ???????????? 0?????? ?????? ??????(?????? ?????????????)
		AbilitySystemComponent->SetTagMapCount(Tag_State_Dead, 0);

		// Health, Mana, Stamina ?????? ?????????.
		SetHealth(GetMaxHealth());
		SetMana(GetMaxMana());
		SetStamina(GetMaxStamina());

		// ?????? GE ??? GA ??????
		AddStartupEffects();
		AddCharacterAbilities();
	}
}

void AGASHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
	StartingCameraBoomLocation = CameraBoom->GetRelativeLocation();
}

void AGASHeroCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(GunComponent && GetMesh())
	{
		GunComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GunSocket");
	}
}

void AGASHeroCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Client??? ????????? ASC ?????????
	AGASPlayerState* PS = GetPlayerState<AGASPlayerState>();
	if(PS)
	{
		// ASC ?????? ??? ActorInfo ?????????
		AbilitySystemComponent = Cast<UGASAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
		BindASCInput();
		
		// AttributeSet ?????? ??? ?????????
		AttributeSet = PS->GetAttributeSet();
		InitializeAttributes();
		
		// ????????? ???????????? ????????? ?????????
		// TODO: State.Dead ???????????? 0?????? ?????? ??????(?????? ?????????????)
		AbilitySystemComponent->SetTagMapCount(Tag_State_Dead, 0);

		// Health, Mana, Stamina ?????? ?????????.
		SetHealth(GetMaxHealth());
		SetMana(GetMaxMana());
		SetStamina(GetMaxStamina());
	}
}

void AGASHeroCharacter::LookUp(float Value)
{
	if(IsAlive())
	{
		AddControllerPitchInput(Value);
	}
}

void AGASHeroCharacter::LookUpRate(float Value)
{
	if(IsAlive())
	{
		AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->DeltaTimeSeconds);
	}
}

void AGASHeroCharacter::Turn(float Value)
{
	if(IsAlive())
	{
		AddControllerYawInput(Value);
	}
}

void AGASHeroCharacter::TurnRate(float Value)
{
	if(IsAlive())
	{
		AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
	}
}

void AGASHeroCharacter::MoveForward(float Value)
{
	const FVector Forward = UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0));
	AddMovementInput(Forward, Value, false);
}

void AGASHeroCharacter::MoveRight(float Value)
{
	const FVector Right = UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0));
	AddMovementInput(Right, Value, false);
}

void AGASHeroCharacter::BindASCInput()
{
	if(!ASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		FGameplayAbilityInputBinds BindInfo(TEXT("ConfirmTarget"),
			TEXT("CancelTarget"), TEXT("EGASAbilityInputID"),
			static_cast<int32>(EGASAbilityInputID::Confirm), static_cast<int32>(EGASAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent( InputComponent, BindInfo);
		ASCInputBound = true;
	}
}
