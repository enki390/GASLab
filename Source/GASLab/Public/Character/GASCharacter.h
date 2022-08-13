// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GASlab/GASTypes.h"
#include "GameFramework/Character.h"
#include "GASCharacter.generated.h"

UCLASS()
class GASLAB_API AGASCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASCharacter(const FObjectInitializer& ObjectInitializer);

	/////////////////////////////////////////////////////////////////
	// Override parent interface
	////////////////////////////////////////////////////////////////
public:
	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/////////////////////////////////////////////////////////////////
	// Attribute accessors
	////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintPure, Category = "GASLab|GASCharacter")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|GASCharacter|Attributes")
	int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|GASCharacter|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|GASCharacter|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|GASCharacter|Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|GASCharacter|Attributes")
	float GetMaxMana() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|GASCharacter|Attributes")
	float GetStamina() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|GASCharacter|Attributes")
	float GetMaxStamina() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|GASCharacter|Attributes")
	float GetMoveSpeed() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|GASCharacter|Attributes")
	float GetMoveSpeedBaseValue() const;

	UFUNCTION(BlueprintPure, Category = "GASLab|GASCharacter")
	virtual int32 GetAbilityLevel(EGASAbilityInputID AbilityID) const;
	
protected:
	virtual void SetHealth(float InHealth);
	virtual void SetMana(float InMana);
	virtual void SetStamina(float InStamina);

	/////////////////////////////////////////////////////////////////
	// Ability system 
	////////////////////////////////////////////////////////////////
protected:
	virtual void AddCharacterAbilities();
	virtual void InitializeAttributes();
	virtual void AddStartupEffects();

	TWeakObjectPtr<class UGASAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UGASCharacterAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASLab|GASCharacter")
	FText CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASLab|Abilities")
	TArray<TSubclassOf<class UGASGameplayAbility>> CharacterAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASLab|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GASLab|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;
};
