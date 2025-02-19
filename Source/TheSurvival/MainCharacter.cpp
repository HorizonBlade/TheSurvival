

#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	JumpMontage = nullptr;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = 125.f;
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckForInteractable();
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForwardBackward", this, &AMainCharacter::MoveForwardBackward);
	InputComponent->BindAxis("MoveRightLeft", this, &AMainCharacter::MoveRightLeft);

	InputComponent->BindAxis("Turn", this, &AMainCharacter::Turn);
	InputComponent->BindAxis("LookUp", this, &AMainCharacter::LookUp);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJumping);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::StopSprint);

	InputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
}

void AMainCharacter::MoveForwardBackward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AMainCharacter::MoveRightLeft(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMainCharacter::Jump()
{
	if (JumpMontage)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(JumpMontage, 1.0f);
		}
	}
	Super::Jump();
	bPressedJump = true;
}

void AMainCharacter::StopJumping()
{
	bPressedJump = false;
	Super::StopJumping();
}

void AMainCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AMainCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMainCharacter::Sprint()
{
	bIsSprint = true;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
}

void AMainCharacter::StopSprint()
{
	bIsSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = 125.0f;
}

void AMainCharacter::CheckForInteractable()
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + (GetActorForwardVector() * 200.0f);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->Implements<UIInteractable>())
		{
			InteractableActor = HitActor;
		}
		else
		{
			InteractableActor = nullptr;
		}
	}
	else
	{
		InteractableActor = nullptr;
	}
}

void AMainCharacter::Interact()
{
	if (InteractableActor)
	{
		IIInteractable* Interactable = Cast<IIInteractable>(InteractableActor);
		if (Interactable)
		{
			Interactable->Interact(this);
		}
	}
}