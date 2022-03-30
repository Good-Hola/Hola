// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	scene = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	check(scene);
	RootComponent = scene;

	weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	check(weapon);
	weapon->SetupAttachment(RootComponent);
	weapon->SetCollisionProfileName(TEXT("HolaWeapon"));

}

int AWeapon::GetDamage()
{
	return damage;
}

EWeaponType AWeapon::GetWeaponType()
{
	return weaponType;
}

FString AWeapon::GetHoldSocketName()
{
	return weaponHoldSocketName;
}

FString AWeapon::GetBackSocketName()
{
	return weaponBackSocketName;
}

UAnimMontage* AWeapon::GetGripAnimMontage()
{
	return GripAnimMontage;
}

void AWeapon::Attack()
{
}