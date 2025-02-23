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

    MaxAmmoInClip = 12;
    CurrentAmmoInClip = MaxAmmoInClip;

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

    if (CurrentAmmoInClip <= 0)
    {
        if (CanReload())
        {
            Reload();
            UE_LOG(LogTemp, Warning, TEXT("No ammo in clip, reloading..."));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("No ammo and cannot reload!"));
        }
        return;
    }

    CurrentAmmoInClip--;

    UE_LOG(LogTemp, Warning, TEXT("Fire! Weapon: %s, Ammo in clip: %d"), *WeaponType.ToString(), CurrentAmmoInClip);

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
    return bIsEquipped && CurrentAmmoInClip > 0;
}

void AGun::Reload()
{
    AMainCharacter* OwnerCharacter = Cast<AMainCharacter>(GetOwner());
    if (!OwnerCharacter) return;

    UInventoryComponent* Inventory = OwnerCharacter->FindComponentByClass<UInventoryComponent>();
    if (!Inventory) return;

    if (!CanReload()) return;

    int32 AmmoInInventory = Inventory->GetItemAmount(FName(RequiredAmmoType));

    int32 AmmoToReload = FMath::Min(AmmoInInventory, MaxAmmoInClip - CurrentAmmoInClip);

    if (AmmoToReload > 0)
    {
        AddAmmo(AmmoToReload);

        Inventory->RemoveItem(FName(RequiredAmmoType), AmmoToReload);

        UE_LOG(LogTemp, Warning, TEXT("Reloaded %d bullets. Ammo in clip: %d, Ammo left: %d"),
            AmmoToReload, CurrentAmmoInClip, AmmoInInventory - AmmoToReload);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Not enough ammo to reload or clip is already full."));
    }
}

bool AGun::CanReload() const
{
    return CurrentAmmoInClip < MaxAmmoInClip;
}

void AGun::AddAmmo(int32 AmmoAmount)
{
    CurrentAmmoInClip = FMath::Min(CurrentAmmoInClip + AmmoAmount, MaxAmmoInClip);
}
