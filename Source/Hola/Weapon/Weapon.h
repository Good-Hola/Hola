// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS(abstract)
class HOLA_API AWeapon : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintGetter = GetDamage, Category = Damage)
		int damage;

	UPROPERTY(VisibleAnywhere, Category = weapon)
		class USkeletalMeshComponent* weapon;

public:	
	AWeapon();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	

	UFUNCTION(BlueprintGetter, Category = Damage)
	int GetDamage();

	//UFUNCTION()
		//virtual void Attack();

};
