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

bool AGASPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

float AGASPlayerState::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float AGASPlayerState::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

float AGASPlayerState::GetHealthRegenRate() const
{
	return AttributeSet->GetHealthRegenRate();
}

float AGASPlayerState::GetMana() const
{
	return AttributeSet->GetMana();
}

float AGASPlayerState::GetMaxMana() const
{
	return AttributeSet->GetMaxMana();
}

float AGASPlayerState::GetManaRegenRate() const
{
	return AttributeSet->GetManaRegenRate();
}

float AGASPlayerState::GetStamina() const
{
	return AttributeSet->GetStamina();
}

float AGASPlayerState::GetMaxStamina() const
{
	return AttributeSet->GetMaxStamina();
}

float AGASPlayerState::GetStaminaRegenRate() const
{
	return AttributeSet->GetStaminaRegenRate();
}

float AGASPlayerState::GetArmor() const
{
	return AttributeSet->GetArmor();
}

float AGASPlayerState::GetMoveSpeed() const
{
	return AttributeSet->GetMoveSpeed();
}

int32 AGASPlayerState::GetCharacterLevel() const
{
	return static_cast<int32>(AttributeSet->GetCharacterLevel());
}

int32 AGASPlayerState::GetXP() const
{
	return static_cast<int32>(AttributeSet->GetXP());
}

int32 AGASPlayerState::GetXPBounty() const
{
	return static_cast<int32>(AttributeSet->GetXPBounty());
}

int32 AGASPlayerState::GetGold() const
{
	return static_cast<int32>(AttributeSet->GetGold());
}

int32 AGASPlayerState::GetGoldBounty() const
{
	return static_cast<int32>(AttributeSet->GetGoldBounty());
}
