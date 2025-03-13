#pragma once

#include "CoreMinimal.h"
#include "MeleeWeapon.h"
#include "KnifeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVAL_API AKnifeWeapon : public AMeleeWeapon
{
	GENERATED_BODY()
public:
	AKnifeWeapon();

protected:
	virtual void Fire() override;
	virtual bool IsMelee() override;
	virtual void Interact(AActor* Interactor) override;
};
