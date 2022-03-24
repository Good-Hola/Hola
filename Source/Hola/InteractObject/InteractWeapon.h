// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractObject.h"
#include "InteractWeapon.generated.h"

/**
 * 
 */
UCLASS()
class HOLA_API AInteractWeapon : public AInteractObject
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		TSubclassOf<class AWeapon> weapon;


public:
	class AWeapon *GetWeapon();
	
};
