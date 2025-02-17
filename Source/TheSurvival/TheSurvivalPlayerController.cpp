// Fill out your copyright notice in the Description page of Project Settings.


#include "TheSurvivalPlayerController.h"
#include "GameFramework/Pawn.h"
#include "MainCharacter.h"

ATheSurvivalPlayerController::ATheSurvivalPlayerController()
{
}

void ATheSurvivalPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATheSurvivalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForwardBackward", this, &ATheSurvivalPlayerController::MoveForwardBackward);
	InputComponent->BindAxis("MoveRightLeft", this, &ATheSurvivalPlayerController::MoveRightLeft);

	InputComponent->BindAxis("Turn", this, &ATheSurvivalPlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &ATheSurvivalPlayerController::LookUp);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ATheSurvivalPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ATheSurvivalPlayerController::StopJumping);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &ATheSurvivalPlayerController::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &ATheSurvivalPlayerController::StopSprint);
}

void ATheSurvivalPlayerController::MoveForwardBackward(float Value)
{
	AMainCharacter* MyCharacter = Cast<AMainCharacter>(GetPawn());
	if (MyCharacter)
	{
		MyCharacter->AddMovementInput(MyCharacter->GetActorForwardVector(), Value);
	}
}

void ATheSurvivalPlayerController::MoveRightLeft(float Value)
{
	AMainCharacter* MyCharacter = Cast<AMainCharacter>(GetPawn());
	if (MyCharacter)
	{
		MyCharacter->AddMovementInput(MyCharacter->GetActorRightVector(), Value);
	}
}

void ATheSurvivalPlayerController::Jump()
{
	AMainCharacter* MyCharacter = Cast<AMainCharacter>(GetPawn());
	if (MyCharacter)
	{
		MyCharacter->Jump();
	}
}

void ATheSurvivalPlayerController::StopJumping()
{
	AMainCharacter* MyCharacter = Cast<AMainCharacter>(GetPawn());
	if (MyCharacter)
	{
		MyCharacter->StopJumping();
	}
}

void ATheSurvivalPlayerController::Turn(float Value)
{
	AddYawInput(Value);
}

void ATheSurvivalPlayerController::LookUp(float Value)
{
	AddPitchInput(Value);
}

void ATheSurvivalPlayerController::Sprint()
{
	APawn* MyPawn = GetPawn();
	if (MyPawn)
	{
		AMainCharacter* MyCharacter = Cast<AMainCharacter>(MyPawn);
		if (MyCharacter)
		{
			MyCharacter->Sprint();
		}
	}
}

void ATheSurvivalPlayerController::StopSprint()
{
	APawn* MyPawn = GetPawn();
	if (MyPawn)
	{
		AMainCharacter* MyCharacter = Cast<AMainCharacter>(MyPawn);
		if (MyCharacter)
		{
			MyCharacter->StopSprint();
		}
	}
}
