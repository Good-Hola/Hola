// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWeapon.h"
#include "../Weapon/Weapon.h"

void AInteractWeapon::Interact_Implementation()
{
	Super::Interact_Implementation();
	//weapon을 character에 저장해줘야함
	UE_LOG(LogTemp, Log, TEXT("child"));
}

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
