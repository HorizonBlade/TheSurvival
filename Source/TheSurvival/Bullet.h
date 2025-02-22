#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
#include "Bullet.generated.h"

UCLASS()
class THESURVIVAL_API ABullet : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:
    ABullet();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void Interact(AActor* Interactor) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
    float Damage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    int32 AmmoPerPack;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* BulletMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    FName AmmoItemID;;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<class ABullet> BulletClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UProjectileMovementComponent* ProjectileMovement;

    UFUNCTION()
    void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};