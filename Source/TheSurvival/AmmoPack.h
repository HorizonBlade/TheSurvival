#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
#include "AmmoPack.generated.h"

UCLASS()
class THESURVIVAL_API AAmmoPack : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	AAmmoPack();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Interact(AActor* Interactor) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 AmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	FName AmmoItemID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* AmmoMesh;
};
