// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacter.h"
#include "GASHeroCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GASLAB_API AGASHeroCharacter : public AGASCharacter
{
	GENERATED_BODY()

public:
	AGASHeroCharacter(const FObjectInitializer& ObjectInitializer);

	/////////////////////////////////////////////////////////////////
	// Override APawn interfaces
	/////////////////////////////////////////////////////////////////
public:
	virtual void PossessedBy(AController* NewController) override;

protected:
	virtual void OnRep_PlayerState() override;
};
