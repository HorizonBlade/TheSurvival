// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVAL_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DaltaSeconds) override;

	APawn* MyCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Direction;
};
