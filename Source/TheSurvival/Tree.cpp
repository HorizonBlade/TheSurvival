#include "Tree.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "InventoryComponent.h"

ATree::ATree()
{
	PrimaryActorTick.bCanEverTick = true;

	bIsFallen = false;
}

void ATree::BeginPlay()
{
	Super::BeginPlay();

	InitialRotation = GetActorRotation();
	TargetRotation = FRotator(90.0f, InitialRotation.Yaw, InitialRotation.Roll);
}

void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsFallen && FallElapsedTime < FallDuration)
	{
		FallElapsedTime += DeltaTime;
		float Alpha = FMath::Clamp(FallElapsedTime / FallDuration, 0.0f, 1.0f);
		FRotator NewRotation = FMath::Lerp(InitialRotation, TargetRotation, Alpha);
		SetActorRotation(NewRotation);

		if (FallElapsedTime >= FallDuration)
		{
			PrimaryActorTick.bCanEverTick = false;
			ResourceMesh->SetEnableGravity(true);
		}
	}
}

void ATree::DestroyResource()
{
	if (!bIsFallen)
	{
		bIsFallen = true;

		ResourceMesh->SetSimulatePhysics(true);
		ResourceMesh->SetEnableGravity(false);
		ResourceMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		ResourceMesh->AddImpulse(FVector(FMath::RandRange(-100.0f, 100.0f), 
								         FMath::RandRange(-100.0f, 100.0f), 
										 0.0f));
	}
}

void ATree::Interact(AActor* Interactor)
{
	if (bIsFallen && Interactor)
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
}
