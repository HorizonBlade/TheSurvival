#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_ItemSlot.generated.h"

UCLASS()
class THESURVIVAL_API UWBP_ItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItem(FName ItemID, int32 Quantity);

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Item;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Quantity;

	UPROPERTY()
	FName CurrentItemID;

	UPROPERTY()
	int32 CurrentQuantity;
};
