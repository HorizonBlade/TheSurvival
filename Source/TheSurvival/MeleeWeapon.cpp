#include "MeleeWeapon.h"
#include "InventoryComponent.h"
#include "Components/StaticMeshComponent.h"



AMeleeWeapon::AMeleeWeapon()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeleeGunMesh"));
    Mesh->SetupAttachment(RootComponent);

    AmmoType = "MeleeWeapon";

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

void AMeleeWeapon::Interact(AActor* Interactor)
{
    if (Interactor)
    {
        UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
        if (Inventory)
        {
            Inventory->AddItem(FName("MeleeWeapon"), 1);
            Destroy();
        }
    }
}
