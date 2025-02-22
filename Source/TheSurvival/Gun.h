#pragma once

#include "CoreMinimal.h"
#include "OtherGun.h"
#include "IInteractable.h"
#include "InventoryComponent.h"
#include "Components/StaticMeshComponent.h"
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
	FName WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName RequiredAmmoType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* GunMesh;

	bool HasAmmoInInventory(UInventoryComponent* Inventory) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool bIsEquipped;

	bool CanFire() const;
};
