// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	weapon->SetupAttachment(RootComponent);
	weapon->SetCollisionProfileName(TEXT("NoCollision"));

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

int AWeapon::GetDamage()
{								
	return damage;
}

