// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GASPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GASLAB_API AGASPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASPlayerState();

	// Begin of IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// End of IAbilitySystemInterface

	class UGASCharacterAttributeSet* GetAttributeSet() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	float GetHealthRegenRate() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	float GetMaxMana() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	float GetManaRegenRate() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	float GetStamina() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	float GetMaxStamina() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	float GetStaminaRegenRate() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	float GetArmor() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	float GetMoveSpeed() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	int32 GetXP() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	int32 GetXPBounty() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	int32 GetGold() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|PlayerState|Attributes")
	int32 GetGoldBounty() const;

protected:
	UPROPERTY()
	class UGASAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UGASCharacterAttributeSet* AttributeSet;
};
