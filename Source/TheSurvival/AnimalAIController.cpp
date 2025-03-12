#include "AnimalAIController.h"
#include "NavigationSystem.h"

AAnimalAIController::AAnimalAIController()
{
}

void AAnimalAIController::BeginPlay()
{
    Super::BeginPlay();
    MoveToRandomLocation();
}

void AAnimalAIController::MoveToRandomLocation()
{
    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn) return;

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!NavSystem) return;

    FVector Origin = ControlledPawn->GetActorLocation();
    FNavLocation NavLocation;

    if (NavSystem->GetRandomPointInNavigableRadius(Origin, 1000.0f, NavLocation))
    {
        MoveToLocation(NavLocation.Location);

        float WaitTime = FMath::RandRange(2.0f, 5.0f);
        GetWorld()->GetTimerManager().SetTimer(TimerHandle_Move, this, &AAnimalAIController::MoveToRandomLocation, WaitTime, false);
    }
}