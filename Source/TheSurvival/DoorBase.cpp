#include "DoorBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"



ADoorBase::ADoorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PivotPoint = CreateDefaultSubobject<USceneComponent>(TEXT("PivotPoint"));
	RootComponent = PivotPoint;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(PivotPoint);

	bIsOpen = false;
}

void ADoorBase::BeginPlay()
{
	Super::BeginPlay();
	
	InitialRotation = GetActorRotation();
	TargetRotation = InitialRotation;
}

void ADoorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOpen)
	{
		FRotator CurrentRotation = GetActorRotation();
		FRotator NewRotation = FMath::Lerp(CurrentRotation, TargetRotation, DeltaTime * DoorOpenSpeed);
		SetActorRotation(NewRotation);
	}
	else
	{
		FRotator CurrentRotation = GetActorRotation();
		FRotator NewRotation = FMath::Lerp(CurrentRotation, InitialRotation, DeltaTime * DoorOpenSpeed);
		SetActorRotation(NewRotation);
	}
}

void ADoorBase::Interact(AActor* Interactor)
{
	if (bIsOpen)
	{
		CloseDoor();
	}
	else
	{
		OpenDoor();
	}
}

void ADoorBase::OpenDoor()
{
	TargetRotation = FRotator(InitialRotation.Pitch, InitialRotation.Yaw + OpenAngle, InitialRotation.Roll);
	bIsOpen = true;
}

void ADoorBase::CloseDoor()
{
	TargetRotation = InitialRotation;
	bIsOpen = false;
}


