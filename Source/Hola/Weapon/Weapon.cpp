// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	scene = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	check(scene);
	RootComponent = scene;

	weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	check(weapon);
	weapon->SetupAttachment(RootComponent);
	weapon->SetCollisionProfileName(TEXT("NoCollision"));

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

int AWeapon::GetDamage()
{								
	return damage;
}

void AWeapon::Attack()
{
}

