#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;

	FInventoryItem() : ItemID(NAME_None), Quantity(1) {}
	FInventoryItem(FName InItemID, int32 InQuantity) : ItemID(InItemID), Quantity(InQuantity) {}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THESURVIVAL_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	bool AddItem(FName ItemID, int32 Quantity = 1);
	bool RemoveItem(FName ItemID, int32 Quantity = 1);
	bool HasItem(FName ItemID) const;

	int32 GetItemAmount(FName ItemID) const;
	bool HasAmmo(FName AmmoID, int32 RequiredAmount) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FInventoryItem> GetItems() const { return Items; }
		
private:
	UPROPERTY()
	TArray<FInventoryItem> Items;
};
