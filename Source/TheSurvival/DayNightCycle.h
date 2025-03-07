#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayNightCycle.generated.h"

UCLASS()
class THESURVIVAL_API ADayNightCycle : public AActor
{
    GENERATED_BODY()

public:
    ADayNightCycle();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(EditAnywhere, Category = "DayNight Settings")
    float DayLength = 3600.0f;

    float TimeOfDay;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class ADirectionalLight* SunLight;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class ADirectionalLight* MoonLight;

    void UpdateSunAndMoon();
};
