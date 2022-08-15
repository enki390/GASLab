// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class EGASHitReactDirection : uint8
{
	None,
	Left,
	Front,
	Right,
	Back,
};

UENUM(BlueprintType)
enum class EGASAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Ability1,
	Ability2,
	Ability3,
	Ability4,
	Ability5,
	Sprint,
	Jump,
};


/////////////////////////////////////////////////////////////////////
// Declare Native GameplayTags
////////////////////////////////////////////////////////////////////

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_HitReact_Front);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_HitReact_Back);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_HitReact_Right);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_HitReact_Left);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_RemoveOnDeath);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_State_Dead);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_State_Debuf_Stun);
