// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Utils/HolaTypes.h"
#include "PlayerAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

UCLASS()
class HOLA_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetCurrentWeaponType, BlueprintSetter = SetCurrentWeaponType, Category = Character)
		EWeaponType currentWeaponType;

public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;

	UPlayerAnimInstance();
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


private:
	UFUNCTION()
		void AnimNotify_AttackHitCheck();
	UFUNCTION()
		void AnimNotify_NextAttackCheck();

public:
	UFUNCTION(BlueprintGetter, Category = Character, meta = (BlueprintThreadSafe))
		EWeaponType GetCurrentWeaponType();

	UFUNCTION(BlueprintSetter, Category = Character)
		void SetCurrentWeaponType(EWeaponType type);

};
