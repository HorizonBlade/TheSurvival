#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OtherGun.generated.h"



UCLASS()
class THESURVIVAL_API AOtherGun : public AActor
{
	GENERATED_BODY()

public:
	AOtherGun();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Fire();
	virtual void Reload();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float AttackRate;

	virtual bool IsMelee();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Ammo;

	UFUNCTION()
	void DealDamage(AActor* HitActor);
};
