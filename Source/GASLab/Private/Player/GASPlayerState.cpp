// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GASPlayerState.h"
#include "AbilitySystem/GASAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/GASCharacterAttributeSet.h"

AGASPlayerState::AGASPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UGASCharacterAttributeSet>("AttributeSet");

	// PlayerState의 기본 NetUpdateFrequency가 너무 낮으므로(업데이트를 많이 하므로) 캐릭터와 비슷한 수준으로 맞춘다.
	NetUpdateFrequency = 100.0f;
	
}

UAbilitySystemComponent* AGASPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UGASCharacterAttributeSet* AGASPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
