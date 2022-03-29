// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Utils/HolaTypes.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HOLA_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance();
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintGetter, Category = Character, meta = (BlueprintThreadSafe))
		EWeaponType GetCurrentWeaponType();

	UFUNCTION(BlueprintSetter, Category = Character)
		void SetCurrentWeaponType(EWeaponType type);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetCurrentWeaponType, BlueprintSetter = SetCurrentWeaponType, Category = Character)
		EWeaponType currentWeaponType;
};
