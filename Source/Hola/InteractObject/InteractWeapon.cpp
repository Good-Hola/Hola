// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWeapon.h"
#include "../Weapon/Weapon.h"

AWeapon *AInteractWeapon::GetWeapon()
{
	UWorld* world = GetWorld();
	if (world)
	{
		AWeapon *newWeapon = world->SpawnActor<AWeapon>(weapon, FVector::ZeroVector, FRotator::ZeroRotator);
		return newWeapon;
	}
	return nullptr;
}
