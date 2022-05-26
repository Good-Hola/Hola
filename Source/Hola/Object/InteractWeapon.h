// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractObject.h"
#include "InteractWeapon.generated.h"

/**
 *
 * 
 */
UCLASS()
class HOLA_API AInteractWeapon : public AInteractObject
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		TSubclassOf<class AWeapon> weapon;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* Particle;

protected:

	UPROPERTY(EditAnywhere, Category = Weapon, meta = (ClampMin = "0", ClampMax = "2", UIMin = "0", UIMax = "2"))
		int rotateDir;

	UPROPERTY(EditAnywhere, Category = Weapon)
		int rotateSpeed;

public:
	AInteractWeapon();

	void Tick(float DeltaSeconds);

	virtual void TurnOn_Implementation(class APlayerCharacter* character);

	virtual void TurnOff_Implementation(class APlayerCharacter* character);

};