#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_AIController.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVAL_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemy_AIController();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float PatrolRadius = 1000.0f;

	void MoveToRandomLocation();
};
