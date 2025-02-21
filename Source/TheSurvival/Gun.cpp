#include "Gun.h"



AGun::AGun()
{
	bIsMalee = false;
	Ammo = 30;
}

void AGun::Fire()
{
	if (Ammo > 0)
	{
		Ammo--;
		UE_LOG(LogTemp, Warning, TEXT("Gun fired! Ammo left: %d"), Ammo);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No ammo! Reload needed."));
	}
}
