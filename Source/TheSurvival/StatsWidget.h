#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainCharacter.h"
#include "StatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVAL_API UStatsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	AMainCharacter* OwningPlayer;

	void SetOwningPlayer(AMainCharacter* Player);
};
