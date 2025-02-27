#include "InventoryComponent.h"
#include "Engine/Engine.h"



UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory Component initialized."));
	Super::BeginPlay();
}

bool UInventoryComponent::AddItem(FName ItemID, int32 Quantity)
{
	if (ItemID.IsNone() || Quantity <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to add item. Invalid ItemID or Quantity."));
		return false;
	}

	for (FInventoryItem& Item : Items)
	{
		if (Item.ItemID == ItemID)
		{
			UE_LOG(LogTemp, Warning, TEXT("Added %d of item %s. New quantity: %d."), Quantity, *ItemID.ToString(), Item.Quantity);
			Item.Quantity += Quantity;
			OnInventoryUpdated.Broadcast();
			return true;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("New item %s added with quantity %d."), *ItemID.ToString(), Quantity);
	Items.Add(FInventoryItem(ItemID, Quantity));
	OnInventoryUpdated.Broadcast();
	return true;
}

bool UInventoryComponent::RemoveItem(FName ItemID, int32 Quantity)
{
	if (ItemID.IsNone() || Quantity <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to remove item. Invalid ItemID or Quantity."));
		return false;
	}

	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ItemID == ItemID)
		{
			if (Items[i].Quantity > Quantity)
			{
				Items[i].Quantity -= Quantity;
				UE_LOG(LogTemp, Warning, TEXT("Removed %d of item %s. New quantity: %d."), Quantity, *ItemID.ToString(), Items[i].Quantity);
				OnInventoryUpdated.Broadcast();
				return true;
			}
			else
			{
				Items.RemoveAt(i);
				UE_LOG(LogTemp, Warning, TEXT("Removed item %s completely."), *ItemID.ToString());
				OnInventoryUpdated.Broadcast();
				return true;
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Item %s not found in inventory."), *ItemID.ToString());
	return false;
}

bool UInventoryComponent::HasItem(FName ItemID) const
{
	for (const FInventoryItem& Item : Items)
	{
		if (Item.ItemID == ItemID)
		{
			UE_LOG(LogTemp, Warning, TEXT("Item %s found in inventory."), *ItemID.ToString());
			return true;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Item %s not found in inventory."), *ItemID.ToString());
	return false;
}

int32 UInventoryComponent::GetItemAmount(FName ItemID) const
{
	for (const FInventoryItem& Item : Items)
	{
		if (Item.ItemID == ItemID)
		{
			UE_LOG(LogTemp, Warning, TEXT("Item %s has quantity %d."), *ItemID.ToString(), Item.Quantity);
			return Item.Quantity;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Item %s not found in inventory."), *ItemID.ToString());
	return 0;
}

bool UInventoryComponent::HasAmmo(FName AmmoID, int32 RequiredAmount) const
{
	return GetItemAmount(AmmoID) >= RequiredAmount;
}