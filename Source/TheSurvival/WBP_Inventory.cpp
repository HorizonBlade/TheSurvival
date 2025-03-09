#include "WBP_Inventory.h"
#include "WBP_ItemSlot.h"
#include "Components/UniformGridPanel.h"
#include "Engine/Engine.h"

void UWBP_Inventory::NativeConstruct()
{
    Super::NativeConstruct();

    UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: NativeConstruct called"));
    UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: NativeConstruct: This: %p"), this);

    if (Inventory)
    {
        Inventory->OnInventoryUpdated.AddDynamic(this, &UWBP_Inventory::RefreshInventory);

        UE_LOG(LogTemp, Warning, TEXT("UniformGridPanel: %p"), UniformGridPanel);

        RefreshInventory();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Inventory is not set!"));
    }
}

void UWBP_Inventory::NativeDestruct()
{
    Super::NativeDestruct();

    UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: NativeDestruct called"));
    UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: NativeDestruct: This: %p"), this);

    if (Inventory)
    {
        Inventory->OnInventoryUpdated.RemoveDynamic(this, &UWBP_Inventory::RefreshInventory);
    }
}

void UWBP_Inventory::SetInventory(UInventoryComponent* InInventory)
{
    UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: SetInventory called"));
    UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: SetInventory: This: %p"), this);

    if (InInventory)
    {
        Inventory = InInventory;
        UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: Inventory set successfully"));

        UE_LOG(LogTemp, Warning, TEXT("Inventory: %p"), Inventory);
        UE_LOG(LogTemp, Warning, TEXT("UniformGridPanel: %p"), UniformGridPanel);

        RefreshInventory();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("UWBP_Inventory: Failed to set inventory! Inventory is null"));
    }
}

void UWBP_Inventory::RefreshInventory()
{
    UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: RefreshInventory called"));
    UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: RefreshInventory: This: %p"), this);

    if (!UniformGridPanel || !Inventory)
    {
        UE_LOG(LogTemp, Error, TEXT("UWBP_Inventory: Invalid UniformGridPanel or Inventory"));
        return;
    }

    UniformGridPanel->ClearChildren();

    TArray<FInventoryItem> Items = Inventory->GetItems();

    if (Items.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: No items in inventory"));
    }
    else
    {
        int32 Column = 0;
        int32 Row = 0;

        for (const FInventoryItem& Item : Items)
        {
            UWBP_ItemSlot* NewItemSlot = CreateWidget<UWBP_ItemSlot>(this, UWBP_ItemSlot::StaticClass());

            if (NewItemSlot)
            {
                UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: ItemSlot created: %p"), NewItemSlot);
                UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: ItemSlot created: This: %p, NewItemSlot: %p"), this, NewItemSlot);

                NewItemSlot->SetItem(Item.ItemID, Item.Quantity);
                UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: SetItem called for ItemID: %s"), *Item.ItemID.ToString());

                UniformGridPanel->AddChildToUniformGrid(NewItemSlot, Row, Column);
                UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: ItemSlot added to UniformGridPanel"));

                Column++;
                if (Column >= 5)
                {
                    Column = 0;
                    Row++;
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("UWBP_Inventory: Failed to create ItemSlot widget"));
            }
        }
    }
}

FText UWBP_Inventory::GetPistolText() const
{
    if (Inventory)
    {
        int32 PistolQuantity = Inventory->GetItemAmount(FName("Pistol"));
        return FText::AsNumber(PistolQuantity);
    }
    return FText::AsNumber(0);
}

FText UWBP_Inventory::GetWoodText() const
{
    if (Inventory)
    {
        int32 WoodQuantity = Inventory->GetItemAmount(FName("Wood"));
        return FText::AsNumber(WoodQuantity);
    }
    return FText::AsNumber(0);
}
