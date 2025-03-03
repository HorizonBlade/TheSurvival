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
	virtual void Reload() override;
	virtual void Interact(AActor* Interactor) override;
	virtual bool IsMelee() override;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 MaxAmmoInClip;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 CurrentAmmoInClip;

	bool CanReload() const;

	UFUNCTION()
	void AddAmmo(int32 AmmoAmount);
};
