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

	class UNavigationSystemV1* NavigationMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float NightSpeedMultiplier = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float EveningStartHour = 18.0f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float PatrolRadius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DetectionRadius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float RandomMoveDelay = 3.0f;

	void MoveToRandomLocation();

	void UpdateEnemySpeed(bool bPlayerDetected);

private:
	FVector RandomLocation;

	bool bIsChasingPlayer;
};
