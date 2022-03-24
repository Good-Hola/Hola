// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	MELEE	UMETA(DisplayName = "Melee"),
	RANGED	UMETA(DisplayName = "Ranged"),
};

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

	UPROPERTY(EditDefaultsOnly, Category = weapon)
		TSubclassOf<class AInteractWeapon> spawnWeapon;

	UPROPERTY(EditDefaultsOnly, Category = weapon)
		FString weaponHoldSocketName;

	UPROPERTY(EditDefaultsOnly, Category = weapon)
		FString weaponBackSocketName;

	UPROPERTY(EditDefaultsOnly, Category = weapon)
		EWeaponType weaponType;

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

	UFUNCTION()
	virtual void Attack();


};
