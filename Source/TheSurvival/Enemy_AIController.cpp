#include "Enemy_AIController.h"
#include "EnemyCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"
#include "TimerManager.h"



AEnemy_AIController::AEnemy_AIController()
{
}

void AEnemy_AIController::BeginPlay()
{
    Super::BeginPlay();

    ACharacter* ControlledCharacter = GetCharacter();
    if (!ControlledCharacter) return;
    MoveToRandomLocation();
    UE_LOG(LogTemp, Warning, TEXT("AIController starting for %s"), *ControlledCharacter->GetName());
}

void AEnemy_AIController::MoveToRandomLocation()
{
    AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(GetPawn());
    if (!Enemy) return;

    float Radius = Enemy->PatrolRadius;

    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    if (!NavSystem) return;

    FNavLocation RandomLocation;
    if (NavSystem->GetRandomReachablePointInRadius(Enemy->GetActorLocation(), Radius, RandomLocation))
    {
        MoveToLocation(RandomLocation.Location);
    }

    float RandomDelay = FMath::RandRange(3.0f, 6.0f);
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemy_AIController::MoveToRandomLocation, RandomDelay, false);
}