#include "Tree.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "InventoryComponent.h"

ATree::ATree()
{
	bIsFallen = false;
}

void ATree::DestroyResource()
{
	if (!bIsFallen)
	{
		bIsFallen = true;

		ResourceMesh->SetSimulatePhysics(true);
		ResourceMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ResourceMesh->AddImpulse(FVector(FMath::RandRange(-100.0f, 100.0f), FMath::RandRange(-100.0f, 100.0f), 0.0f));
		ResourceMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}
}

void ATree::Interact(AActor* Interactor)
{
	if (Interactor)
	{
		UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
		if (Inventory)
		{
			Inventory->AddItem(FName("Tree"), 5);

			Destroy();
		}
	}
}
