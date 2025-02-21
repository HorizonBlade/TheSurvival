#include "OtherGun.h"
#include <Kismet/GameplayStatics.h>



AOtherGun::AOtherGun()
{
	PrimaryActorTick.bCanEverTick = false;

	Damage = 25.0f;
	AttackRate = 1.0f;
	bIsMalee = false;
	Ammo = 10;
}

void AOtherGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOtherGun::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon fired!"));
}

void AOtherGun::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon reloaded!"));
}

void AOtherGun::DealDamage(AActor* HitActor)
{
	if (HitActor)
	{
		UGameplayStatics::ApplyDamage(HitActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());
	}
}
