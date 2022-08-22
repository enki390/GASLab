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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void OnRep_PlayerState() override;

public:
	class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	USkeletalMeshComponent* GetGunComponent() const { return GunComponent; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseTurnRate = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseLookUpRate = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float StartingCameraBoomArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FVector StartingCameraBoomLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* GunComponent;

	bool ASCInputBound = false;

	/////////////////////////////////////////////////////////////////
	// Input
	/////////////////////////////////////////////////////////////////
protected:
	void LookUp(float Value);
	void LookUpRate(float Value);
	void Turn(float Value);
	void TurnRate(float Value);
	void MoveForward(float Value);
	void MoveRight(float Value);

	void BindASCInput();
};
