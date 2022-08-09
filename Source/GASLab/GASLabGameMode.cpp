// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASLabGameMode.h"
#include "GASLabCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGASLabGameMode::AGASLabGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
