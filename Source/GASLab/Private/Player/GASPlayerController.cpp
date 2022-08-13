// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GASPlayerController.h"

#include "AbilitySystemComponent.h"
#include "Player/GASPlayerState.h"

void AGASPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AGASPlayerState* PS = GetPlayerState<AGASPlayerState>();
	if (PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}

void AGASPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}
