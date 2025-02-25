#include "Enemy_AIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void AEnemy_AIController::AEnemyCharacter()
{
}

void AEnemy_AIController::BeginPlay()
{
    Super::BeginPlay();

    ACharacter* ControlledCharacter = GetCharacter();
    if (!ControlledCharacter) return;

    UE_LOG(LogTemp, Warning, TEXT("AIController starting for %s"), *ControlledCharacter->GetName());
}
