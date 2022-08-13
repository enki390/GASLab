// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Heros/GASHeroCharacter.h"
#include "AbilitySystem/GASAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/GASCharacterAttributeSet.h"
#include "Player/GASPlayerController.h"
#include "Player/GASPlayerState.h"

AGASHeroCharacter::AGASHeroCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AGASHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// [서버] ASC 초기화
	AGASPlayerState* PS = GetPlayerState<AGASPlayerState>();
	if(PS)
	{
		// ASC 인스턴스 캐싱 및 ActorInfo 초기화
		AbilitySystemComponent = Cast<UGASAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		// AttributeSet 인스턴스 캐싱 후 초기화
		AttributeSet = PS->GetAttributeSet();
		InitializeAttributes();

		// 이후는 리스폰에 관련된 작업들
		// TODO: State.Dead 카운트를 0으로 강제 설정(어떤 효과일까?)
		AbilitySystemComponent->SetTagMapCount(Tag_State_Dead, 0);

		// Health, Mana, Stamina 직접 초기화.
		SetHealth(GetMaxHealth());
		SetMana(GetMaxMana());
		SetStamina(GetMaxStamina());

		// 기본 GE 및 GA 등록
		AddStartupEffects();
		AddCharacterAbilities();
	}
}

void AGASHeroCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Client는 여기서 ASC 초기화
	AGASPlayerState* PS = GetPlayerState<AGASPlayerState>();
	if(PS)
	{
		// ASC 캐싱 및 ActorInfo 초기화
		AbilitySystemComponent = Cast<UGASAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		// AttributeSet 캐싱 및 초기화
		AttributeSet = PS->GetAttributeSet();
		InitializeAttributes();
		
		// 이후는 리스폰에 관련된 작업들
		// TODO: State.Dead 카운트를 0으로 강제 설정(어떤 효과일까?)
		AbilitySystemComponent->SetTagMapCount(Tag_State_Dead, 0);

		// Health, Mana, Stamina 직접 초기화.
		SetHealth(GetMaxHealth());
		SetMana(GetMaxMana());
		SetStamina(GetMaxStamina());
	}
}
