#include "Gun.h"
#include "InventoryComponent.h"
#include "Components/StaticMeshComponent.h"



AGun::AGun()
{
    GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetupAttachment(RootComponent);

	bIsMalee = false;
	Ammo = 30;
    AmmoType = "Pistol";
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

void AGun::Interact(AActor* Interactor)
{
    if (Interactor)
    {
        UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
        if (Inventory)
        {
            Inventory->AddItem(FName("Gun"), 1);
            Destroy(); 
        }
    }
}
