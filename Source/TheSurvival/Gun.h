#pragma once

#include "CoreMinimal.h"
#include "OtherGun.h"
#include "IInteractable.h"
#include "Gun.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVAL_API AGun : public AOtherGun, public IIInteractable
{
	GENERATED_BODY()
	
public:
	AGun();

	virtual void Fire() override;
	virtual void Interact(AActor* Interactor) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName AmmoType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* GunMesh;
};
