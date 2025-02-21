#include "MeleeWeapon.h"



AMeleeWeapon::AMeleeWeapon()
{
	bIsMalee = true;
}

void AMeleeWeapon::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee attack!"));
}
