// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GASGameplayAbility.h"

#include "AbilitySystemComponent.h"

UGASGameplayAbility::UGASGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	ActivationBlockedTags.AddTag(Tag_State_Dead);
	ActivationBlockedTags.AddTag(Tag_State_Debug_Stun);
}

void UGASGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if(ActivateAbilityOnGranted)
	{
		bool ActivatedAbiliyty = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
