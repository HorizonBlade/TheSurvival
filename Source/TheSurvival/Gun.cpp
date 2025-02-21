#include "Gun.h"



AGun::AGun()
{
	bIsMalee = false;
	Ammo = 30;
}

void AGun::Fire()
{
	if (Ammo > 0)
	{
		Ammo--;

        FHitResult HitResult;
        FVector Start = GetActorLocation();
        FVector ForwardVector = GetActorForwardVector();
        FVector End = Start + (ForwardVector * 5000);

        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this);

        if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
        {
            DealDamage(HitResult.GetActor());
        }

        UE_LOG(LogTemp, Warning, TEXT("Gun fired! Ammo left: %d"), Ammo);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No ammo! Reload needed."));
	}
}
