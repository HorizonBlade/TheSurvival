#include "AnimalBase.h"
#include "AnimalAIController.h"
#include "AnimalAIController.h"
#include "InventoryComponent.h"
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
    if (bIsDead) return;

    bIsDead = true;
    SkinHealth = 100;
    UE_LOG(LogTemp, Warning, TEXT("The animal has been killed. Now we have to skin it!"));

    if (GetCharacterMovement())
    {
        GetCharacterMovement()->DisableMovement();
    }

    if (GetController())
    {
        GetController()->UnPossess();
    }

    if (GetMesh())
    {
        GetMesh()->SetSimulatePhysics(true);
        GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

        FVector Impulse = FVector(FMath::RandRange(-200, 200), FMath::RandRange(-200, 200), 0);
        GetMesh()->AddImpulse(Impulse, NAME_None, true);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AAnimalBase::Die() - Mesh is nullptr!"));
    }
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

void AAnimalBase::TakeSkinDamage(float Damage)
{
    if (!bIsDead || bCanBeSkinned) return;

    SkinHealth -= Damage;
    UE_LOG(LogTemp, Warning, TEXT("The skin is damaged. Remaining: %f"), SkinHealth);

    if (SkinHealth <= 0)
    {
        bCanBeSkinned = true;
        UE_LOG(LogTemp, Warning, TEXT("You can now pick up the hide through Interact!"));
    }
}

void AAnimalBase::Interact(AActor* Interactor)
{
    if (!bCanBeSkinned) return;

    UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
    if (Inventory)
    {
        Inventory->AddItem(FName("AnimalSkin"), 2);
        UE_LOG(LogTemp, Warning, TEXT("The hide has been added to the inventory!"));
    }

    Destroy();
}