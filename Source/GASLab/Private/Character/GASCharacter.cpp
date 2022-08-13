// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASCharacter.h"
#include "AbilitySystem/GASAbilitySystemComponent.h"
#include "AbilitySystem/GASGameplayAbility.h"
#include "AbilitySystem/Attributes/GASCharacterAttributeSet.h"


// Sets default values
AGASCharacter::AGASCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* AGASCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

bool AGASCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 AGASCharacter::GetCharacterLevel() const
{
	if (AttributeSet.IsValid())
	{
		return static_cast<int32>(AttributeSet->GetCharacterLevel());
	}
	return 0;
}

float AGASCharacter::GetHealth() const
{
	if (AttributeSet.IsValid())
	{
		return AttributeSet->GetHealth();
	}
	return 0.0f;
}

float AGASCharacter::GetMaxHealth() const
{
	if (AttributeSet.IsValid())
	{
		return AttributeSet->GetMaxHealth();
	}
	return 0.0f;
}

float AGASCharacter::GetMana() const
{
	if (AttributeSet.IsValid())
	{
		return AttributeSet->GetMana();
	}
	return 0.0f;
}

float AGASCharacter::GetMaxMana() const
{
	if (AttributeSet.IsValid())
	{
		return AttributeSet->GetMaxMana();
	}
	return 0.0f;
}

float AGASCharacter::GetStamina() const
{
	if (AttributeSet.IsValid())
	{
		return AttributeSet->GetStamina();
	}
	return 0.0f;
}

float AGASCharacter::GetMaxStamina() const
{
	if (AttributeSet.IsValid())
	{
		return AttributeSet->GetMaxStamina();
	}
	return 0.0f;
}

float AGASCharacter::GetMoveSpeed() const
{
	if (AttributeSet.IsValid())
	{
		return AttributeSet->GetMoveSpeed();
	}
	return 0.0f;
}

float AGASCharacter::GetMoveSpeedBaseValue() const
{
	if (AttributeSet.IsValid())
	{
		return AttributeSet->GetMoveSpeedAttribute().GetGameplayAttributeData(AttributeSet.Get())->GetBaseValue();
	}
	return 0.0f;
}

int32 AGASCharacter::GetAbilityLevel(EGASAbilityInputID AbilityID) const
{
	return 1;
}

void AGASCharacter::SetHealth(float InHealth)
{
	if (AttributeSet.IsValid())
	{
		AttributeSet->SetHealth(InHealth);
	}
}

void AGASCharacter::SetMana(float InMana)
{
	if (AttributeSet.IsValid())
	{
		AttributeSet->SetMana(InMana);
	}
}

void AGASCharacter::SetStamina(float InStamina)
{
	if (AttributeSet.IsValid())
	{
		AttributeSet->SetStamina(InStamina);
	}
}

void AGASCharacter::AddCharacterAbilities()
{
	if (HasAuthority() && AbilitySystemComponent.IsValid() && !AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		// Grant abilities
		for (auto& Ability : CharacterAbilities)
		{
			FGameplayAbilitySpec Spec(Ability, GetAbilityLevel(Ability.GetDefaultObject()->AbilityID),
				static_cast<int32>(Ability.GetDefaultObject()->InputID), this);
			AbilitySystemComponent->GiveAbility(Spec);
		}
		AbilitySystemComponent->CharacterAbilitiesGiven = true;
	}
}

void AGASCharacter::InitializeAttributes()
{
	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	if (!IsValid(DefaultAttributes))
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."),
		       *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
		DefaultAttributes, GetCharacterLevel(), EffectContext);
	if (SpecHandle.IsValid())
	{
		FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
			*SpecHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

void AGASCharacter::AddStartupEffects()
{
	if (HasAuthority() && AbilitySystemComponent.IsValid() && !AbilitySystemComponent->StartupEffectsApplied)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		for (auto GE : StartupEffects)
		{
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
				GE, GetCharacterLevel(), EffectContext);
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
					*SpecHandle.Data.Get(), AbilitySystemComponent.Get());
			}
		}
		AbilitySystemComponent->StartupEffectsApplied = true;
	}
}
