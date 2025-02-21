#pragma once

#include "CoreMinimal.h"
#include "OtherGun.h"
#include "Gun.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVAL_API AGun : public AOtherGun
{
	GENERATED_BODY()
	
public:
	AGun();

	virtual void Fire() override;
};
