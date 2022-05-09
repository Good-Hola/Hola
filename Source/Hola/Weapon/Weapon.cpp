// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "../Object/InteractWeapon.h"
#include "../Character/PlayerCharacter.h"

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

FString AWeapon::GetGripAnimSectionName()
{
	return GripAnimSectionName;
}

FString AWeapon::GetUnGripAnimSectionName()
{
	return UnGripAnimSectionName;
}

void AWeapon::SetAnimInstance(UPlayerAnimInstance* instance)
{
	animInstance = instance;
}

void AWeapon::Attack()
{
}

void AWeapon::SpawnInteractWeapon(APlayerCharacter* character)
{
	if (character && weapon && GetWorld())
	{
		AInteractWeapon* newWeapon = GetWorld()->SpawnActor<AInteractWeapon>(spawnWeapon,
			character->GetActorLocation(), character->GetActorRotation());
		newWeapon->GetMesh()->AddForce(character->GetActorRotation().Vector() * 300000);
		Destroy();
	}
}

void AWeapon::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
}
