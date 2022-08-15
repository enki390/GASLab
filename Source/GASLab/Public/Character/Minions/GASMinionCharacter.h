// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacter.h"
#include "GASMinionCharacter.generated.h"

/**
 * AI 캐릭터 클래스
 * AI는 서버에서 돌아가므로 ASC 및 AttributeSet 인스턴스를 캐릭터가 소유하도록 했다.
 * 때문에 ASC 초기화도 BeginPlay()에서 하도록 했다. 
 */
UCLASS()
class GASLAB_API AGASMinionCharacter : public AGASCharacter
{
	GENERATED_BODY()

public:
	AGASMinionCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(Transient)
	class UGASAbilitySystemComponent* MinionASC;

	UPROPERTY(Transient)
	class UGASCharacterAttributeSet* MinionAttributeSet;

	
	
	
};
