#include "BaseResource.h"



ABaseResource::ABaseResource()
{
	PrimaryActorTick.bCanEverTick = true;

	ResourceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResourceMesh"));
	ResourceMesh->SetupAttachment(RootComponent);

	Health = 500.0f;
}

float ABaseResource::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Resource took %f damage, health left: %f"), DamageAmount, Health);

	if (Health <= 0)
	{
		DestroyResource();
	}

	return DamageAmount;
}

void ABaseResource::DestroyResource()
{
	UE_LOG(LogTemp, Warning, TEXT("Resource mesh was broken"));
}
