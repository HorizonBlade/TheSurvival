#pragma once

#include "CoreMinimal.h"
#include "BaseResource.h"
#include "IInteractable.h"
#include "Tree.generated.h"

/**
 *
 */
UCLASS()
class THESURVIVAL_API ATree : public ABaseResource, public IIInteractable
{
	GENERATED_BODY()

public:
	ATree();

	virtual void DestroyResource() override;
	virtual void Interact(AActor* Interactor) override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	float FallDuration = 2.0f;

	UPROPERTY()
	float FallElapsedTime = 0.0f;

	UPROPERTY()
	FRotator InitialRotation;

	UPROPERTY()
	FRotator TargetRotation;

private:
	bool bIsFallen;
};
