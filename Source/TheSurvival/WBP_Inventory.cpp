#include "WBP_Inventory.h"
#include "Engine/Engine.h"

void UWBP_Inventory::NativeConstruct()
{
    Super::NativeConstruct();

    UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: NativeConstruct called"));
    UE_LOG(LogTemp, Warning, TEXT("UWBP_Inventory: NativeConstruct: This: %p"), this);

    if (Inventory)
    {
        Inventory->OnInventoryUpdated.AddDynamic(this, &UWBP_Inventory::RefreshInventory);
        RefreshInventory();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Inventory is not set!"));
    }

    if (CraftsButton)
    {
        CraftsButton->OnClicked.AddDynamic(this, &UWBP_Inventory::OnCraftsButtonClicked);
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

    if (!Inventory)
    {
        UE_LOG(LogTemp, Error, TEXT("UWBP_Inventory: Inventory is null"));
        return;
    }
    if (Pistol_Quantity)
    {
        Pistol_Quantity->SetText(GetPistolText());
    }
    if (Wood_Quantity)
    {
        Wood_Quantity->SetText(GetWoodText());
    }
    if (Ammo_Quantity)
    {
        Ammo_Quantity->SetText(GetAmmoText());
    }
    if (Axe_Quantity)
    {
        Axe_Quantity->SetText(GetAxeText());
    }
    if (Rock_Quantity)
    {
        Rock_Quantity->SetText(GetRockText());
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

FText UWBP_Inventory::GetAmmoText() const
{
    if (Inventory)
    {
        int32 AmmoQuantity = Inventory->GetItemAmount(FName("PistolAmmo"));
        return FText::AsNumber(AmmoQuantity);
    }
    return FText::AsNumber(0);
}

FText UWBP_Inventory::GetAxeText() const
{
    if (Inventory)
    {
        int32 AxeQuantity = Inventory->GetItemAmount(FName("MeleeWeapon"));
        return FText::AsNumber(AxeQuantity);
    }
    return FText::AsNumber(0);
}

FText UWBP_Inventory::GetRockText() const
{
    if (Inventory)
    {
        int32 RockQuantity = Inventory->GetItemAmount(FName("Rock"));
        return FText::AsNumber(RockQuantity);
    }
    return FText::AsNumber(0);
}

void UWBP_Inventory::OnCraftsButtonClicked()
{
    if (CraftsWidgetClass)
    {
        if (!ActiveWidget)
        {
            ActiveWidget = CreateWidget<UUserWidget>(GetWorld(), CraftsWidgetClass);
        }

        if (ActiveWidget && !ActiveWidget->IsInViewport())
        {
            ActiveWidget->AddToViewport();
        }
    }
}