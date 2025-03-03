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

private:
	bool bIsFallen;
};
