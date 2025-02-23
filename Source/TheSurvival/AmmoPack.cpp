#include "AmmoPack.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"



AAmmoPack::AAmmoPack()
{
    PrimaryActorTick.bCanEverTick = true;

    AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
    RootComponent = AmmoMesh;

    AmmoCount = 15;
    AmmoItemID = FName("PistolAmmo");
}

void AAmmoPack::BeginPlay()
{
    Super::BeginPlay();
}

void AAmmoPack::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAmmoPack::Interact(AActor* Interactor)
{
    if (Interactor)
    {
        UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
        if (Inventory)
        {
            Inventory->AddItem(AmmoItemID, AmmoCount);

            Destroy();
        }
    }
}
