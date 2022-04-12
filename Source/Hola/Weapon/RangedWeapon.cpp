// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"
#include "Projectile.h"
#include "../Character/PlayerCharacter.h"

ARangedWeapon::ARangedWeapon()
{
	projSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjtileSpawn"));
	projSpawn->SetupAttachment(RootComponent);
}

void ARangedWeapon::Attack()
{
	if (projectile)
	{
		if (GetWorld())
		{
			GetWorld()->SpawnActor<AProjectile>(projectile,
				projSpawn->GetComponentLocation(), projSpawn->GetComponentRotation());
		}
	}

}
