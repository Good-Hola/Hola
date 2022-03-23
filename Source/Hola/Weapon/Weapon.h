// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class HOLA_API AWeapon : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintGetter = GetDamage, Category = Damage)
		int damage;

	UPROPERTY(VisibleAnywhere, Category = Scene)
		class USceneComponent* scene;

	UPROPERTY(VisibleAnywhere, Category = weapon)
		class USkeletalMeshComponent* weapon;

public:	
	AWeapon();

protected:
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintGetter, Category = Damage)
	int GetDamage();

	UFUNCTION()
	virtual void Attack();


};
