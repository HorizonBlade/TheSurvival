#include "MeleeWeapon.h"
#include "MainCharacter.h"
#include "InventoryComponent.h"
#include "Components/StaticMeshComponent.h"



AMeleeWeapon::AMeleeWeapon()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeleeGunMesh"));
    Mesh->SetupAttachment(RootComponent);

    WeaponType = "MeleeWeapon";

    bIsEquipped = false;
	bIsMalee = true;
}

void AMeleeWeapon::Fire()
{
    AMainCharacter* OwnerCharacter = Cast<AMainCharacter>(GetOwner());
    if (!OwnerCharacter) return;

    FVector EyeLocation;
    FRotator EyeRotation;
    OwnerCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotation);

    FVector Start = EyeLocation;
    FVector ForwardVector = EyeRotation.Vector();
    FVector End = Start + (ForwardVector * 5000);

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);
    CollisionParams.AddIgnoredActor(OwnerCharacter);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Pawn, CollisionParams))
    {
        DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red, false, 1.0f, 0, 1.0f);
        DrawDebugSphere(GetWorld(), HitResult.Location, 10.0f, 12, FColor::Blue, false, 1.0f, 0, 1.0f);

        DealDamage(HitResult.GetActor());
    }
}

void AMeleeWeapon::Interact(AActor* Interactor)
{
    if (Interactor)
    {
        UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
        if (Inventory)
        {
            Inventory->AddItem(FName("MeleeWeapon"), 1);
            SetActorHiddenInGame(true);
            SetActorEnableCollision(false);
        }
    }
}
