// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	MyCharacter = TryGetPawnOwner();


}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MyCharacter != nullptr)
	{
		FVector Velocity = MyCharacter->GetVelocity();
		Speed = Velocity.Size();

		// Вычисляем направление (Direction)
		FRotator Rotation = MyCharacter->GetActorRotation();
		Direction = CalculateDirection(Velocity, Rotation);
	}

}
