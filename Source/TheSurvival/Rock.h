#pragma once

#include "CoreMinimal.h"
#include "BaseResource.h"
#include "IInteractable.h"
#include "Rock.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVAL_API ARock : public ABaseResource, public IIInteractable
{
	GENERATED_BODY()
	
public:
    ARock();
protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    virtual void Interact(AActor* Interactor) override;
    virtual void DestroyResource() override;

private:
    bool bIsBroken;
};
