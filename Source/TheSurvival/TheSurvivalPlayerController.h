// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheSurvivalPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVAL_API ATheSurvivalPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATheSurvivalPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void MoveForwardBackward(float Value);
	void MoveRightLeft(float Value);

	void Jump();
	void StopJumping();

	void Turn(float Value);
	void LookUp(float Value);
};
