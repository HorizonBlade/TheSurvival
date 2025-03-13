

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

class UUserWidget;
class UStatsWidget;

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

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* CrouchMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* CrouchWalkMontage;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float Health = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float Hunger = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float Thirst = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float HungerDecreaseRate = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float ThirstDecreaseRate = 0.6f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float SprintMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> StatsWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UUserWidget* StatsWidget;

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

	void StartCrouch();
	void StopCrouch();

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

	void StartHungerThirstTimer();
	void ApplyHungerThirstEffects();

	void Eat(float Amount);
	void Drink(float Amount);

	void Die();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetHungerPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetThirstPercent() const;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UWBP_Inventory> InventoryWidgetClass;

	UWBP_Inventory* InventoryWidget;

private:
	AActor* InteractableActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	float LastFootstepTime = 0.0f;

	FTimerHandle HungerThirstTimer;
};
