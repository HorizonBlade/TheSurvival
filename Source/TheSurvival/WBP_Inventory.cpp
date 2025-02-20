#include "WBP_Inventory.h"
#include "WBP_ItemSlot.h"
#include "Components/UniformGridPanel.h"
#include "Engine/Engine.h"

void UWBP_Inventory::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWBP_Inventory::SetInventory(UInventoryComponent* InInventory)
{
	if (InInventory)
	{
		Inventory = InInventory;
		UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: Inventory set successfully"));
		RefreshInventory();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_Inventory: Failed to set inventory! Inventory is null"));
	}
}

void UWBP_Inventory::RefreshInventory()
{
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

	int32 Column = 0;
	int32 Row = 0;

	for (const FInventoryItem& Item : Items)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: Creating slot for Item: %s, Quantity: %d"), *Item.ItemID.ToString(), Item.Quantity);

		UWBP_ItemSlot* ItemSlot = CreateWidget<UWBP_ItemSlot>(this, UWBP_ItemSlot::StaticClass());

		if (ItemSlot)
		{
			UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: Successfully created ItemSlot widget"));
			ItemSlot->SetItem(Item.ItemID, Item.Quantity);
			UniformGridPanel->AddChildToUniformGrid(ItemSlot, Row, Column);

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
