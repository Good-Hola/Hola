// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Utils/HolaTypes.h"
#include "Weapon.generated.h"

UCLASS()
class HOLA_API AWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetDamage, Category = weapon)
		int damage;

	UPROPERTY(VisibleAnywhere, Category = Scene)
		class USceneComponent* scene;

	UPROPERTY(VisibleAnywhere, Category = weapon)
		class USkeletalMeshComponent* weapon;

	UPROPERTY(EditDefaultsOnly, Category = weapon)
		TSubclassOf<class AInteractWeapon> spawnWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetHoldSocketName, Category = weapon)
		FString weaponHoldSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetBackSocketName, Category = weapon)
		FString weaponBackSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetWeaponType, Category = weapon)
		EWeaponType weaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetGripAnimMontage, Category = anim)
		UAnimMontage* GripAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetGripAnimSectionName, Category = anim)
		FString GripAnimSectionName;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetUnGripAnimSectionName, Category = anim)
		FString UnGripAnimSectionName;

public:
	AWeapon();

public:
	UFUNCTION(BlueprintGetter, Category = weapon)
		int GetDamage();

	UFUNCTION(BlueprintGetter, Category = weapon)
		EWeaponType GetWeaponType();

	UFUNCTION(BlueprintGetter, Category = weapon)
		FString GetHoldSocketName();

	UFUNCTION(BlueprintGetter, Category = weapon)
		FString GetBackSocketName();

	UFUNCTION(BlueprintGetter, Category = anim)
		UAnimMontage* GetGripAnimMontage();

	UFUNCTION(BlueprintGetter, Category = anim)
		FString GetGripAnimSectionName();

	UFUNCTION(BlueprintGetter, Category = anim)
		FString GetUnGripAnimSectionName();

	UFUNCTION()
		virtual void Attack();

	UFUNCTION()
		void SpawnInteractWeapon(class APlayerCharacter *character);


};