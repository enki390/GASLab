// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GASCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASLAB_API UGASCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	class FGASSavedMove : public FSavedMove_Character
	{
	public:
		typedef FSavedMove_Character Super;

		// Reset all saved variables
		virtual void Clear() override;
		// Store input commands in the compressed flags
		virtual uint8 GetCompressedFlags() const override;

		// This is used to check whether or not two moves can be combined into one.
		// Basically you just check to make sure that the saved variables are the same.
		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;

		// Sets up the move before sending it to the server.
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;

		// Sets variables on characcter movement component before making a predictive correction.
		virtual void PrepMoveFor(ACharacter* C) override;
		
		uint8 SavedRequestToStartSprinting : 1;
		uint8 SavedRequestToStartADS : 1;
	};

	class FGASNetworkPredictionData_Client : public FNetworkPredictionData_Client_Character
	{
	public:
		FGASNetworkPredictionData_Client(const UCharacterMovementComponent& ClientMovement);

		typedef FNetworkPredictionData_Client_Character Super;

		virtual FSavedMovePtr AllocateNewMove() override;
	};
	
public:
	UGASCharacterMovementComponent();

	virtual float GetMaxSpeed() const override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual class FNetworkPredictionData_Client* GetPredictionData_Client() const override;

	// Sprint
	UFUNCTION(BlueprintCallable, Category = "Sprint")
	void StartSprinting();

	UFUNCTION(BlueprintCallable, Category = "Sprint")
	void StopSprinting();

	// Aim Down Sights
	UFUNCTION(BlueprintCallable, Category = "Aim Down Sights")
	void StartAimDownSights();

	UFUNCTION(BlueprintCallable, Category = "Aim Down Sights")
	void StopAimDownSights();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float SprintSpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aim Down Sights")
	float ADSSpeedMultiplier;
	
	uint8 RequestToStartSprinting : 1;
	uint8 RequestToStartADS : 1;
	
};
