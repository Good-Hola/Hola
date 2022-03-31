// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"

ARangedWeapon::ARangedWeapon()
{

}

void ARangedWeapon::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Warning, TEXT("in ranged weapon"));

}
