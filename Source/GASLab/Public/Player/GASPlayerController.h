// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GASPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GASLAB_API AGASPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Begin of APlayerController interface
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnRep_PlayerState() override;
	// End of APlayerController interface
};
