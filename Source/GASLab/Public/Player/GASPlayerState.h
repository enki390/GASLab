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

protected:
	UPROPERTY()
	class UGASAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UGASCharacterAttributeSet* AttributeSet;
};
