#include "WBP_ItemSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"

void UWBP_ItemSlot::SetItem(FName ItemID, int32 Quantity)
{
	UE_LOG(LogTemp, Warning, TEXT("UWBP_ItemSlot: Setting Item %s with Quantity %d"), *ItemID.ToString(), Quantity);

	CurrentItemID = ItemID;
	CurrentQuantity = Quantity;

	// Here will be the logic to display the image or other data for the item
	if (Text_Quantity)
	{
		Text_Quantity->SetText(FText::AsNumber(Quantity));
	}

	// Example: loading an image for an item
	if (Image_Item)
	{
	// For example, a blank image if the item ID is unknown
		Image_Item->SetBrushFromTexture(nullptr);
	}
}
