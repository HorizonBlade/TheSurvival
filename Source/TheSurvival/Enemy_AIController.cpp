#include "Enemy_AIController.h"
#include "EnemyCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"
#include "MainCharacter.h"
#include "TimerManager.h"



AEnemy_AIController::AEnemy_AIController()
{
}

void AEnemy_AIController::BeginPlay()
{
    Super::BeginPlay();

    NavigationMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

    ACharacter* ControlledCharacter = GetCharacter();
    if (!ControlledCharacter) return;
    MoveToRandomLocation();
    UE_LOG(LogTemp, Warning, TEXT("AIController starting for %s"), *ControlledCharacter->GetName());
}

void AEnemy_AIController::MoveToRandomLocation()
{
    AActor* DetectedPlayer = UGameplayStatics::GetActorOfClass(GetWorld(), AMainCharacter::StaticClass());

    if (DetectedPlayer)
    {
        float DistanceToPlayer = FVector::Dist(GetPawn()->GetActorLocation(), DetectedPlayer->GetActorLocation());

        if (DistanceToPlayer <= DetectionRadius)
        {
            MoveToActor(DetectedPlayer);
        }
        else
        {
            if (NavigationMesh)
            {
                NavigationMesh->K2_GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(), RandomLocation, PatrolRadius);
                MoveToLocation(RandomLocation);

                FTimerHandle PointDelay;
                GetWorld()->GetTimerManager().SetTimer(PointDelay, this, &AEnemy_AIController::MoveToRandomLocation, RandomMoveDelay, false, -1.0f);
            }
        }
    }
}
