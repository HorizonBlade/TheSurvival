#include "Gun.h"
#include "MainCharacter.h"
#include "InventoryComponent.h"
#include "Components/StaticMeshComponent.h"



AGun::AGun()
{
    GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetupAttachment(RootComponent);

	bIsMalee = false;
	bIsEquipped = false;

    WeaponType = "Pistol";
    RequiredAmmoType = "PistolAmmo";
}

void AGun::Fire()
{
	if (!CanFire()) return;

	AMainCharacter* OwnerCharacter = Cast<AMainCharacter>(GetOwner());
	if (!OwnerCharacter) return;

	UInventoryComponent* Inventory = OwnerCharacter->FindComponentByClass<UInventoryComponent>();
	if (!Inventory) return;

	if (!HasAmmoInInventory(Inventory))
	{
		UE_LOG(LogTemp, Warning, TEXT("Нет патронов для стрельбы!"));
		return;
	}

	Inventory->RemoveItem(RequiredAmmoType, 1);

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

	UE_LOG(LogTemp, Warning, TEXT("Выстрел! Оружие: %s, Осталось патронов: %s"), *WeaponType.ToString(), *RequiredAmmoType.ToString());
}

void AGun::Interact(AActor* Interactor)
{
    if (Interactor)
    {
        UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
        if (Inventory)
        {
			Inventory->AddItem(FName("Gun"), 1);

			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
        }
    }
}

bool AGun::HasAmmoInInventory(UInventoryComponent* Inventory) const
{
	return Inventory && Inventory->HasItem(RequiredAmmoType);
}

bool AGun::CanFire() const
{
	return bIsEquipped && HasAmmoInInventory(Cast<AMainCharacter>(GetOwner())->FindComponentByClass<UInventoryComponent>());
}
