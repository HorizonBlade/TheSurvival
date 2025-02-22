#include "InventoryComponent.h"



UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UInventoryComponent::AddItem(FName ItemID, int32 Quantity)
{
	if (ItemID.IsNone() || Quantity <= 0) return false;

	for (FInventoryItem& Item : Items)
	{
		if (Item.ItemID == ItemID)
		{
			Item.Quantity += Quantity;
			return true;
		}
	}
	Items.Add(FInventoryItem(ItemID, Quantity));
	return true;
}

bool UInventoryComponent::RemoveItem(FName ItemID, int32 Quantity)
{
	if (ItemID.IsNone() || Quantity <= 0) return false;

	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ItemID == ItemID)
		{
			if (Items[i].Quantity > Quantity)
			{
				Items[i].Quantity -= Quantity;
				return true;
			}
			else
			{
				Items.RemoveAt(i);
				return true;
			}
		}
	}
	return false;
}

bool UInventoryComponent::HasItem(FName ItemID) const
{
	for (const FInventoryItem& Item : Items)
	{
		if (Item.ItemID == ItemID)
		{
			return true;
		}
	}
	return false;
}

int32 UInventoryComponent::GetItemAmount(FName ItemID) const
{
	for (const FInventoryItem& Item : Items)
	{
		if (Item.ItemID == ItemID)
		{
			return Item.Quantity;
		}
	}
	return 0;
}

bool UInventoryComponent::HasAmmo(FName AmmoID, int32 RequiredAmount) const
{
	return GetItemAmount(AmmoID) >= RequiredAmount;
}