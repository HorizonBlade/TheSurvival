// Fill out your copyright notice in the Description page of Project Settings.


#include "TheSurvivalGameMode.h"
#include "MainCharacter.h"
#include "TheSurvivalPlayerController.h"



ATheSurvivalGameMode::ATheSurvivalGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> MainCharacterFinder(TEXT("/Game/Blueprints/BP_MainCharacter"));

    if (MainCharacterFinder.Succeeded())
    {
        DefaultPawnClass = MainCharacterFinder.Class;
    }

    PlayerControllerClass = ATheSurvivalPlayerController::StaticClass();
}

void ATheSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
}
