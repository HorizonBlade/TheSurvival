#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "WBP_Inventory.generated.h"

UCLASS()
class THESURVIVAL_API UWBP_Inventory : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

public:
    void SetInventory(UInventoryComponent* InInventory);

    UFUNCTION()
    void RefreshInventory();

private:
    UPROPERTY(meta = (BindWidget))
    class UUniformGridPanel* UniformGridPanel;

    UPROPERTY()
    UInventoryComponent* Inventory;
};