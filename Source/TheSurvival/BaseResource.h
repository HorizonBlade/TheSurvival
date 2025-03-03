#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseResource.generated.h"

UCLASS()
class THESURVIVAL_API ABaseResource : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseResource();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ResourceMesh")
	UStaticMeshComponent* ResourceMesh;
public:	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	virtual void DestroyResource();
};
