#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
#include "DoorBase.generated.h"

UCLASS()
class THESURVIVAL_API ADoorBase : public AActor, public IIInteractable
{
	GENERATED_BODY()

public:
	ADoorBase();

protected:
	virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void Interact(AActor* Interactor) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* DoorMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent* PivotPoint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    float OpenAngle = 90.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    float DoorOpenSpeed = 3.0f;
private:
    bool bIsOpen;
    FRotator InitialRotation;
    FRotator TargetRotation;

    void OpenDoor();
    void CloseDoor();
};
