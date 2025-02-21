#include "MeleeWeapon.h"



AMeleeWeapon::AMeleeWeapon()
{
	bIsMalee = true;
}

void AMeleeWeapon::Fire()
{
    FVector Start = GetActorLocation();
    FVector End = Start + (GetActorForwardVector() * 200);

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    if (GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(50), CollisionParams))
    {
        DealDamage(HitResult.GetActor());
    }

    UE_LOG(LogTemp, Warning, TEXT("Melee attack!"));
}
