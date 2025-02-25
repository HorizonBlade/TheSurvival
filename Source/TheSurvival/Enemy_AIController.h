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
	void AEnemyCharacter();

protected:
	virtual void BeginPlay() override;
};
