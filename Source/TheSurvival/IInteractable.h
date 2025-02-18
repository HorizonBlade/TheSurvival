#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UIInteractable : public UInterface
{
    GENERATED_BODY()
};

/**
 * An interface for objects that can be interacted with.
 */
class THESURVIVAL_API IIInteractable
{
    GENERATED_BODY()

public:
    virtual void Interact(AActor* Interactor) = 0;
};