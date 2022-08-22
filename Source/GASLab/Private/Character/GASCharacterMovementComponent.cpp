// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASCharacterMovementComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GASAbilitySystemComponent.h"
#include "Character/GASCharacter.h"

void UGASCharacterMovementComponent::FGASSavedMove::Clear()
{
	Super::Clear();

	SavedRequestToStartSprinting = false;
	SavedRequestToStartADS = false;
}

uint8 UGASCharacterMovementComponent::FGASSavedMove::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if(SavedRequestToStartSprinting)
	{
		Result |= FLAG_Custom_0;
	}

	if(SavedRequestToStartADS)
	{
		Result |= FLAG_Custom_1;
	}

	return Result;
}

bool UGASCharacterMovementComponent::FGASSavedMove::CanCombineWith(const FSavedMovePtr& NewMove,
	ACharacter* InCharacter, float MaxDelta) const
{
	if(SavedRequestToStartSprinting != ((FGASSavedMove*)&NewMove)->SavedRequestToStartSprinting)
	{
		return false;
	}

	if(SavedRequestToStartADS != ((FGASSavedMove*)&NewMove)->SavedRequestToStartADS)
	{
		return false;
	}
	return Super::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

void UGASCharacterMovementComponent::FGASSavedMove::SetMoveFor(ACharacter* C, float InDeltaTime,
	FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	UGASCharacterMovementComponent* CharacterMovement = Cast<UGASCharacterMovementComponent>(C->GetCharacterMovement());
	if(CharacterMovement)
	{
		SavedRequestToStartSprinting = CharacterMovement->RequestToStartSprinting;
		SavedRequestToStartADS = CharacterMovement->RequestToStartADS;
	}
}

void UGASCharacterMovementComponent::FGASSavedMove::PrepMoveFor(ACharacter* C)
{
	Super::PrepMoveFor(C);
}

UGASCharacterMovementComponent::FGASNetworkPredictionData_Client::FGASNetworkPredictionData_Client(
	const UCharacterMovementComponent& ClientMovement)
		: Super(ClientMovement)
{
}

FSavedMovePtr UGASCharacterMovementComponent::FGASNetworkPredictionData_Client::AllocateNewMove()
{
	return FSavedMovePtr(new FGASSavedMove());
}

UGASCharacterMovementComponent::UGASCharacterMovementComponent()
{
	SprintSpeedMultiplier = 1.4f;
	ADSSpeedMultiplier = 0.5f;
}

float UGASCharacterMovementComponent::GetMaxSpeed() const
{
	AGASCharacter* Owner = GetOwner<AGASCharacter>();
	if(!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() No Owner"), *FString(__FUNCTION__));
		return Super::GetMaxSpeed();
	}

	if(!Owner->IsAlive())
	{
		return 0.0f;
	}

	if(Owner->GetAbilitySystemComponent()->HasMatchingGameplayTag(Tag_State_Debuf_Stun))
	{
		return 0.0f;
	}

	if(RequestToStartSprinting)
	{
		return Owner->GetMoveSpeed() * SprintSpeedMultiplier;
	}

	if(RequestToStartADS)
	{
		return Owner->GetMoveSpeed() * ADSSpeedMultiplier;
	}
	
	return Owner->GetMoveSpeed();
}

void UGASCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	RequestToStartSprinting = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
	RequestToStartADS = (Flags & FSavedMove_Character::FLAG_Custom_1) != 0;
}

FNetworkPredictionData_Client* UGASCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != nullptr);

	if(!ClientPredictionData)
	{
		UGASCharacterMovementComponent* MutableThis = const_cast<UGASCharacterMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FGASNetworkPredictionData_Client(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.0f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.0f;
	}
	return ClientPredictionData;
}

void UGASCharacterMovementComponent::StartSprinting()
{
	RequestToStartSprinting = true;
}

void UGASCharacterMovementComponent::StopSprinting()
{
	RequestToStartSprinting = false;
}

void UGASCharacterMovementComponent::StartAimDownSights()
{
	RequestToStartADS = true;
}

void UGASCharacterMovementComponent::StopAimDownSights()
{
	RequestToStartADS = false;
}
