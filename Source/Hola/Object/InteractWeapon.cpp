// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWeapon.h"
#include "../Weapon/Weapon.h"
#include "../Character/PlayerCharacter.h"

AInteractWeapon::AInteractWeapon()
{
	mesh->SetCollisionObjectType(ECC_GameTraceChannel5);
	mesh->SetCollisionProfileName(TEXT("HolaWeapon"));
	mesh->SetSimulatePhysics(true);

	SKMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKMesh"));
	check(SKMesh);
	SKMesh->SetupAttachment(RootComponent);
	SKMesh->SetCollisionObjectType(ECC_GameTraceChannel5);
	SKMesh->SetCollisionProfileName(TEXT("HolaWeapon"));
	SKMesh->SetSimulatePhysics(true);
}

void AInteractWeapon::TurnOn_Implementation(APlayerCharacter* character)
{
	if (character && weapon && GetWorld())
	{
		AWeapon* newWeapon = GetWorld()->SpawnActor<AWeapon>(weapon, character->GetActorLocation(), character->GetActorRotation());
		character->SetWeapon(newWeapon);
		Destroy();
	}

}

void AInteractWeapon::TurnOff_Implementation(APlayerCharacter* character)
{
	UE_LOG(LogTemp, Log, TEXT("this is weapon turn off"));

}