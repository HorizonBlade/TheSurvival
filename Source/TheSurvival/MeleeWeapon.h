#pragma once

#include "CoreMinimal.h"
#include "OtherGun.h"
#include "IInteractable.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVAL_API AMeleeWeapon : public AOtherGun, public IIInteractable
{
	GENERATED_BODY()
	
public:
	AMeleeWeapon();

	virtual void Fire() override;
	virtual bool IsMelee() override;
	virtual void Interact(AActor* Interactor) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* Mesh;

	bool bIsEquipped;
};
