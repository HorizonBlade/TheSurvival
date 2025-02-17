

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

	JumpMontage = nullptr;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJumping);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::StopSprint);
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
}

void AMainCharacter::StopJumping()
{
	Super::StopJumping();
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