#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalBase.generated.h"

UCLASS()
class THESURVIVAL_API AAnimalBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAnimalBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void FleeFromPlayer(AActor* Player);
public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resources")
	int MeatAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Resources")
	int SkinAmount;


	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	void Die();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RunSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DetectionRadius = 600.0f;

};
