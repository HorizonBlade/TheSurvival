#include "Rock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "InventoryComponent.h"


ARock::ARock()
{
    PrimaryActorTick.bCanEverTick = true;
    bIsBroken = false;
}

void ARock::BeginPlay()
{
    Super::BeginPlay();
}

void ARock::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ARock::DestroyResource()
{
    bIsBroken = true;
}

void ARock::Interact(AActor* Interactor)
{
    if (bIsBroken && Interactor)
    {
        if (Interactor)
        {
            UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
            if (Inventory)
            {
                Inventory->AddItem(FName("Rock"), 3);

                Destroy();
            }
        }
    }
}