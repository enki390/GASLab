// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Minions/GASMinionCharacter.h"

#include "AbilitySystem/GASAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/GASCharacterAttributeSet.h"

AGASMinionCharacter::AGASMinionCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MinionASC = CreateDefaultSubobject<UGASAbilitySystemComponent>("AbilitySystemComponent");
	MinionASC->SetIsReplicated(true);
	MinionASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AbilitySystemComponent = MinionASC;

	MinionAttributeSet = CreateDefaultSubobject<UGASCharacterAttributeSet>(TEXT("AttributeSet"));
	AttributeSet = MinionAttributeSet;
}

void AGASMinionCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitializeAttributes();
		AddStartupEffects();
		AddCharacterAbilities();
	}
}
