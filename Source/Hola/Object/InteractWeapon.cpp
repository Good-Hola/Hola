// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWeapon.h"
#include "../Weapon/Weapon.h"
#include "Particles/ParticleSystemComponent.h"
#include "../Character/PlayerCharacter.h"

AInteractWeapon::AInteractWeapon()
{
	mesh->SetCollisionProfileName(TEXT("InteractWeapon"));

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	check(Particle); 
	Particle->SetupAttachment(RootComponent);
}

void AInteractWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (mesh)
	{
		switch (rotateDir)
		{
			case 0:
				mesh->AddLocalRotation(FRotator(DeltaSeconds * rotateSpeed, 0.f, 0.f));
				break;
			case 1:
				mesh->AddLocalRotation(FRotator(0.f, DeltaSeconds * rotateSpeed, 0.f));
				break;
			case 2:
				mesh->AddLocalRotation(FRotator(0.f, 0.f, DeltaSeconds * rotateSpeed));
				break;
			default:
				break;
		}

	}

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