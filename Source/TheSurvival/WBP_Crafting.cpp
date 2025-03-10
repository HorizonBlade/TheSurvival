#include "WBP_Crafting.h"
#include "Components/CanvasPanel.h"

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
    RemoveFromParent();
}