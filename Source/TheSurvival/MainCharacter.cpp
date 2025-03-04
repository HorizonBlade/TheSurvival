

#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "EngineUtils.h"
#include "StatsWidget.h"
#include <Kismet/GameplayStatics.h>

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

	Health = 100.0f;
	Hunger = 100.0f;
	Thirst = 100.0f;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = 125.f;
	StartHungerThirstTimer();

	UE_LOG(LogTemp, Warning, TEXT("Starting parameters: Health=%f, Hunger=%f, Thirst=%f"), Health, Hunger, Thirst);

	if (StatsWidgetClass)
	{
		StatsWidget = CreateWidget<UUserWidget>(GetWorld(), StatsWidgetClass);
		if (StatsWidget && Cast<UStatsWidget>(StatsWidget))
		{
			Cast<UStatsWidget>(StatsWidget)->SetOwningPlayer(this);
		}
		if (StatsWidget)
		{
			StatsWidget->AddToViewport();
		}
	}

}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckForInteractable();

	if (GetVelocity().Size() > 10.f && GetCharacterMovement()->IsMovingOnGround())
	{
		float Speed = GetVelocity().Size();
		float StepInterval = Speed > 300.f ? 0.35f : 0.5f;

		if (GetWorld()->TimeSeconds - LastFootstepTime > StepInterval)
		{
			PlayFootstepSound();
			LastFootstepTime = GetWorld()->TimeSeconds;
		}
	}
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

	InputComponent->BindAction("Inventory", IE_Pressed, this, &AMainCharacter::ToggleInventory);

	InputComponent->BindAction("EquipWeapon", IE_Pressed, this, &AMainCharacter::EquipWeapon);
	InputComponent->BindAction("EquipWeapon2", IE_Pressed, this, &AMainCharacter::EquipWeapon2);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AMainCharacter::Fire);
	InputComponent->BindAction("Reload", IE_Pressed, this, &AMainCharacter::Reload);
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

	if (JumpSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, JumpSound, GetActorLocation());
	}
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

void AMainCharacter::ToggleInventory()
{
	if (!InventoryWidget)
	{
		InventoryWidget = CreateWidget<UWBP_Inventory>(GetWorld(), InventoryWidgetClass);
		if (InventoryWidget)
		{
			InventoryWidget->SetInventory(InventoryComponent);
			InventoryWidget->AddToViewport();
		}
	}
	else
	{
		InventoryWidget->RemoveFromParent();
		InventoryWidget = nullptr;
	}
}

void AMainCharacter::EquipWeapon()
{
	if (!InventoryComponent) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->SetActorHiddenInGame(true);
		CurrentWeapon->bIsEquipped = false;
		CurrentWeapon = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Weapons stowed in inventory."));
		return;
	}

	if (!InventoryComponent->HasItem(FName("Pistol")))
	{
		UE_LOG(LogTemp, Warning, TEXT("You don't have a gun in your inventory!"));
		return;
	}

	for (TActorIterator<AGun> It(GetWorld()); It; ++It)
	{
		AGun* Gun = *It;
		if (Gun && Gun->WeaponType == "Pistol" && Gun->IsHidden())
		{
			CurrentWeapon = Gun;
			break;
		}
	}

	if (!CurrentWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("No gun found for the outfit!"));
		return;
	}

	CurrentWeapon->SetActorHiddenInGame(false);
	CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "WeaponSocket");
	CurrentWeapon->SetOwner(this);
	CurrentWeapon->bIsEquipped = true;

	UE_LOG(LogTemp, Warning, TEXT("You equipped the gun!"));
}

void AMainCharacter::EquipWeapon2()
{
	if (!InventoryComponent) return;

	if (MeleeWeapon)
	{
		MeleeWeapon->SetActorHiddenInGame(true);
		MeleeWeapon->bIsEquipped = false;
		MeleeWeapon = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("MeleeWeapon stowed in inventory."));
		return;
	}

	if (!InventoryComponent->HasItem(FName("MeleeWeapon")))
	{
		UE_LOG(LogTemp, Warning, TEXT("You don't have a MeleeWeapon in your inventory!"));
		return;
	}

	for (TActorIterator<AMeleeWeapon> It(GetWorld()); It; ++It)
	{
		if (*It && (*It)->WeaponType == "MeleeWeapon" && (*It)->IsHidden())
		{
			MeleeWeapon = *It;
			break;
		}
	}

	if (!MeleeWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("No MeleeWeapon found for the outfit!"));
		return;
	}

	MeleeWeapon->SetActorHiddenInGame(false);
	MeleeWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "WeaponSocket");
	MeleeWeapon->SetOwner(this);
	MeleeWeapon->bIsEquipped = true;

	UE_LOG(LogTemp, Warning, TEXT("You equipped the MeleeWeapon!"));
}


void AMainCharacter::Fire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Fire();
	}
	else if (MeleeWeapon)
	{
		MeleeWeapon->Fire();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No weapon equipped!"));
	}
}

void AMainCharacter::Reload()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Reload();
	}
}

void AMainCharacter::PlayFootstepSound()
{
	if (!GetCharacterMovement()->IsMovingOnGround()) return;

	USoundBase* SoundToPlay = GetVelocity().Size() > 300.f ? RunSound : WalkSound;

	if (SoundToPlay)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay, GetActorLocation());
	}
}

void AMainCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (LandSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LandSound, GetActorLocation());
	}
}

void AMainCharacter::StartHungerThirstTimer()
{
	GetWorld()->GetTimerManager().SetTimer(HungerThirstTimer, this, &AMainCharacter::ApplyHungerThirstEffects, 5.0f, true);
}

void AMainCharacter::ApplyHungerThirstEffects()
{
	float HungerLoss = HungerDecreaseRate * (bIsSprint ? SprintMultiplier : 1.0f);
	float ThirstLoss = ThirstDecreaseRate * (bIsSprint ? SprintMultiplier : 1.0f);

	Hunger = FMath::Clamp(Hunger - HungerLoss, 0.0f, 100.0f);
	Thirst = FMath::Clamp(Thirst - ThirstLoss, 0.0f, 100.0f);

	UE_LOG(LogTemp, Warning, TEXT("Parameters decreased: Health=%f, Hunger=%f, Thirst=%f"), Health, Hunger, Thirst)

	if (Hunger == 0.0f || Thirst == 0.0f)
	{
		Health = FMath::Clamp(Health - 5.0f, 0.0f, 100.0f);
		if (Health <= 0.0f)
		{
			Die();
		}
	}
}

void AMainCharacter::Eat(float Amount)
{
	Hunger = FMath::Clamp(Hunger + Amount, 0.0f, 100.0f);
	UE_LOG(LogTemp, Warning, TEXT("Eaten: Hunger=%f"), Hunger);
}

void AMainCharacter::Drink(float Amount)
{
	Thirst = FMath::Clamp(Thirst + Amount, 0.0f, 100.0f);
	UE_LOG(LogTemp, Warning, TEXT("Drunk: Thirst=%f"), Thirst);
}

void AMainCharacter::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("player is dead"));
}

float AMainCharacter::GetHealthPercent() const
{
	return Health / 100.0f;
}

float AMainCharacter::GetHungerPercent() const
{
	return Hunger / 100.0f;
}

float AMainCharacter::GetThirstPercent() const
{
	return Thirst / 100.0f;
}