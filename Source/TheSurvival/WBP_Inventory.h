#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "Components/TextBlock.h"
#include <Components/Button.h>
#include "WBP_Inventory.generated.h"

UCLASS()
class THESURVIVAL_API UWBP_Inventory : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    UPROPERTY(meta = (BindWidget))
    UButton* CraftsButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* Pistol_Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* Wood_Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* Ammo_Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* Axe_Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* Rock_Quantity;
public:
    void SetInventory(UInventoryComponent* InInventory);

    UFUNCTION()
    void RefreshInventory();

    UFUNCTION(BlueprintCallable)
    FText GetPistolText() const;

    UFUNCTION(BlueprintCallable)
    FText GetWoodText() const;

    UFUNCTION(BlueprintCallable)
    FText GetAmmoText() const;

    UFUNCTION(BlueprintCallable)
    FText GetAxeText() const;

    UFUNCTION(BlueprintCallable)
    FText GetRockText() const;

    UFUNCTION()
    void OnCraftsButtonClicked();
    UUserWidget* ActiveWidget = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TSubclassOf<UUserWidget> CraftsWidgetClass;

private:

    UPROPERTY()
    UInventoryComponent* Inventory;
};