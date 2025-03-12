#include "AnimalBase.h"
#include "AnimalAIController.h"
#include "AnimalAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


AAnimalBase::AAnimalBase()
{
	PrimaryActorTick.bCanEverTick = true;

    Health = 100.0f;
    MeatAmount = 5.0f;
    SkinAmount = 2.0f;

    AIControllerClass = AAnimalAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn) return;

    float Distance = FVector::Dist(GetActorLocation(), PlayerPawn->GetActorLocation());
    if (Distance < DetectionRadius)
    {
        FleeFromPlayer(PlayerPawn);
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }
}

float AAnimalBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Health -= DamageAmount;
    UE_LOG(LogTemp, Warning, TEXT("Animal took %f damage, health left: %f"), DamageAmount, Health);

    if (Health <= 0)
    {
        Die();
    }
    return DamageAmount;
}

void AAnimalBase::Die()
{
}

void AAnimalBase::FleeFromPlayer(AActor* Player)
{
    if (!Player) return;

    GetCharacterMovement()->MaxWalkSpeed = RunSpeed;

    FVector PlayerLocation = Player->GetActorLocation();
    FVector AnimalLocation = GetActorLocation();
    FVector FleeDirection = (AnimalLocation - PlayerLocation).GetSafeNormal();
    FVector FleeTarget = AnimalLocation + FleeDirection * 1000.0f;

    AAnimalAIController* AIController = Cast<AAnimalAIController>(GetController());
    if (AIController)
    {
        AIController->MoveToLocation(FleeTarget);
    }
}