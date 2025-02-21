#pragma once

#include "CoreMinimal.h"
#include "OtherGun.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVAL_API AMeleeWeapon : public AOtherGun
{
	GENERATED_BODY()
	
public:
	AMeleeWeapon();

	virtual void Fire() override;
};
