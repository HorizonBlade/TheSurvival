

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "IInteractable.h"
#include "InventoryComponent.h"
#include "WBP_Inventory.h"
#include "Gun.h"
#include "MeleeWeapon.h"
#include "MainCharacter.generated.h"

UCLASS()
class THESURVIVAL_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JumpAnimations")
	UAnimMontage* JumpMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	AGun* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	AMeleeWeapon* MeleeWeapon;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* WalkSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* RunSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* JumpSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* LandSound;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForwardBackward(float Value);
	void MoveRightLeft(float Value);

	void Jump();
	void StopJumping();

	void Turn(float Value);
	void LookUp(float Value);

	void Sprint();
	void StopSprint();

	bool bIsSprint;
	bool bPressedJump;

	void Interact();
	void CheckForInteractable();

	void ToggleInventory();

	void EquipWeapon();
	void EquipWeapon2();
	void Fire();
	void Reload();

	void PlayFootstepSound();

	void Landed(const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UWBP_Inventory> InventoryWidgetClass;

	UWBP_Inventory* InventoryWidget;


private:
	AActor* InteractableActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	float LastFootstepTime = 0.0f;
};
