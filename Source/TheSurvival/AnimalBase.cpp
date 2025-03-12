#include "AnimalBase.h"


AAnimalBase::AAnimalBase()
{
	PrimaryActorTick.bCanEverTick = true;

    Health = 100.0f;
    MeatAmount = 5.0f;
    SkinAmount = 2.0f;
}

void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AAnimalBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Health -= DamageAmount;
    UE_LOG(LogTemp, Warning, TEXT("Animal took %f damage, health left: %f"), DamageAmount, Health);

    if (Health <= 0)
    {
        Die();
    }
    return DamageAmount;
}

void AAnimalBase::Die()
{
}
