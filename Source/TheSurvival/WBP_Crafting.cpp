#include "WBP_Crafting.h"
#include "Components/CanvasPanel.h"
#include "WBP_Inventory.h"

void UWBP_Crafting::NativeConstruct()
{
    Super::NativeConstruct();

    if (BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &UWBP_Crafting::OnBackButtonClicked);
    }
}

void UWBP_Crafting::OnBackButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("UWBP_Crafting: OnBackButtonClicked called"));
    RemoveFromParent();

    if (OwningInventoryWidget)
    {
        OwningInventoryWidget->ActiveWidget = nullptr;
    }
}