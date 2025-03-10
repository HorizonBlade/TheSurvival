#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "WBP_Inventory.h"
#include "WBP_Crafting.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVAL_API UWBP_Crafting : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override;
public:

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UButton* BackButton;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    class UWBP_Inventory* OwningInventoryWidget;

    UFUNCTION()
    void OnBackButtonClicked();
};
