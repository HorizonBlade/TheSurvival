#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AnimalAIController.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVAL_API AAnimalAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAnimalAIController();

protected:
	virtual void BeginPlay() override;

public:
	void MoveToRandomLocation();

	class UNavigationSystemV1* NavigationMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float RandomMoveDelay = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float PatrolRadius = 1000.0f;

private:
	FTimerHandle TimerHandle_Move;
};
