#include "DayNightCycle.h"
#include "Engine/DirectionalLight.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Components/LightComponent.h"


ADayNightCycle::ADayNightCycle()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADayNightCycle::BeginPlay()
{
    Super::BeginPlay();

    TimeOfDay = 0.0f;

    TArray<AActor*> Lights;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), Lights);

    for (AActor* Light : Lights)
    {
        ADirectionalLight* DirLight = Cast<ADirectionalLight>(Light);
        if (DirLight)
        {
            if (SunLight == nullptr || DirLight->GetLightComponent()->Intensity > 10000.0f)
            {
                SunLight = DirLight;
            }
            else
            {
                MoonLight = DirLight;
            }
        }
    }

    if (!MoonLight)
    {
        FActorSpawnParameters SpawnParams;
        MoonLight = GetWorld()->SpawnActor<ADirectionalLight>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

        if (MoonLight)
        {
            ULightComponent* MoonLightComp = MoonLight->GetLightComponent();
            if (MoonLightComp)
            {
                MoonLightComp->SetIntensity(0.0f);
                MoonLightComp->SetLightColor(FLinearColor(0.2f, 0.2f, 0.5f));
            }
        }
    }

    if (SunLight)
    {
        SunLight->GetLightComponent()->SetMobility(EComponentMobility::Movable);
    }

    if (MoonLight)
    {
        MoonLight->GetLightComponent()->SetMobility(EComponentMobility::Movable);
    }
}

void ADayNightCycle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeOfDay += DeltaTime;
    if (TimeOfDay >= DayLength)
    {
        TimeOfDay = 0.0f;
    }

    UpdateSunAndMoon();
}

void ADayNightCycle::UpdateSunAndMoon()
{
    float SunAngle = (TimeOfDay / DayLength) * 360.0f;

    if (SunLight)
    {
        SunLight->SetActorRotation(FRotator(SunAngle - 180, -30.0f, 0.0f));

        float SunIntensity = FMath::Clamp(FMath::Sin(FMath::DegreesToRadians(SunAngle)), 0.0f, 1.0f) * 100000.0f;
        SunLight->GetLightComponent()->SetIntensity(SunIntensity);
    }

    if (MoonLight)
    {
        float MoonAngle = SunAngle + 180.0f;
        MoonLight->SetActorRotation(FRotator(MoonAngle - 180.0f, -30.0f, 0.0f));

        float MoonIntensity = FMath::Clamp(FMath::Sin(FMath::DegreesToRadians(MoonAngle)), 0.0f, 1.0f) * 50000.0f;
        MoonLight->GetLightComponent()->SetIntensity(MoonIntensity);
    }
}