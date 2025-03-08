#include "EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"



AEnemyCharacter::AEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    Health = 100.0f;
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = 250.0f;
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
    AController* EventInstigator, AActor* DamageCauser)
{
    Health -= DamageAmount;
    UE_LOG(LogTemp, Warning, TEXT("Enemy took %f damage, health left: %f"), DamageAmount, Health);

    if (Health <= 0)
    {
        Destroy();
    }

    return DamageAmount;
}