#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "Components/TextBlock.h"
#include "WBP_Inventory.generated.h"

UCLASS()
class THESURVIVAL_API UWBP_Inventory : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* Pistol_Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* Wood_Quantity;
public:
    void SetInventory(UInventoryComponent* InInventory);

    UFUNCTION()
    void RefreshInventory();

    UFUNCTION(BlueprintCallable)
    FText GetPistolText() const;

    UFUNCTION(BlueprintCallable)
    FText GetWoodText() const;
private:
    UPROPERTY(meta = (BindWidget))
    class UUniformGridPanel* UniformGridPanel;

    UPROPERTY()
    UInventoryComponent* Inventory;
};