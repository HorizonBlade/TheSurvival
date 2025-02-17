// Fill out your copyright notice in the Description page of Project Settings.


#include "TheSurvivalGameMode.h"
#include "MainCharacter.h"
#include "TheSurvivalPlayerController.h"



ATheSurvivalGameMode::ATheSurvivalGameMode()
{
	DefaultPawnClass = AMainCharacter::StaticClass();

	PlayerControllerClass = ATheSurvivalPlayerController::StaticClass();
}

void ATheSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
}
