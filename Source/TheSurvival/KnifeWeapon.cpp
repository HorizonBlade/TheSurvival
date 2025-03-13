#include "KnifeWeapon.h"
#include "MainCharacter.h"

AKnifeWeapon::AKnifeWeapon()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KnifeMesh"));
    Mesh->SetupAttachment(RootComponent);

    WeaponType = "KnifeWeapon";

    bIsEquipped = false;
}

void AKnifeWeapon::Fire()
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

bool AKnifeWeapon::IsMelee()
{
	return true;
}

void AKnifeWeapon::Interact(AActor* Interactor)
{
    if (Interactor)
    {
        UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
        if (Inventory)
        {
            Inventory->AddItem(FName("Knife"), 1);
            SetActorHiddenInGame(true);
            SetActorEnableCollision(false);
        }
    }
}