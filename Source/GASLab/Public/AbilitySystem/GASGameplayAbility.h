// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GASlab/GASTypes.h"
#include "GASGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASLAB_API UGASGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGASGameplayAbility();
	
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	EGASAbilityInputID InputID = EGASAbilityInputID::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	EGASAbilityInputID AbilityID = EGASAbilityInputID::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	bool ActivateAbilityOnGranted = false;
};
