// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Utils/HolaTypes.h"
#include "PlayerCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FSwapWeaponDelegate, EWeaponType);


UCLASS()
class HOLA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetMaxHealth, BlueprintSetter = SetHealth, Category = Stat)
		float max_hp;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetMaxEnergy, Category = Stat)
		float max_energy;

	UPROPERTY(BlueprintGetter = GetHealth, BlueprintSetter = SetHealth, Category = Stat)
		float health;

	UPROPERTY(BlueprintGetter = GetEnergy, BlueprintSetter = SetEnergy, Category = Stat)
		float energy;
	UPROPERTY(BlueprintGetter = GetOtherActor, BlueprintSetter = SetOtherActor, Category = Stat)
		AActor* TakeOtherActor;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "TriggerCapsule")
		class UCapsuleComponent* TriggerCapsule;
	UPROPERTY(EditInstanceOnly)
		class UWidgetComponent* widget;

	class AInteractObject* focusedActor;

	UPROPERTY(BlueprintGetter = GetPlayerAnimInstance, Category = Instance)
	class UPlayerAnimInstance* animInstance;

	UPROPERTY()
		TArray<class AWeapon*> weapon;

	UPROPERTY(BlueprintGetter = GetCurrentWeapon, BlueprintSetter = SetCurrentWeapon, Category = Stat)
		EWeaponType currentWeaponIndex;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	//bool isCrouching

	FSwapWeaponDelegate SwapWeaponDelegate;

	UFUNCTION(BlueprintNativeEvent)
		void Death();
	virtual void Death_Implementation();

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	//void StartCrouch();

	//void StopCrouch();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual	void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void SwapWeapon(EWeaponType type);

	void Attack();

	void DropWeapon();


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		void OnTriggerBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnTriggerEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetWeapon(class AWeapon* newWeapon);

	UFUNCTION(BlueprintGetter, Category = Stat)
		float GetHealth();

	UFUNCTION(BlueprintGetter, Category = Stat)
		float GetEnergy();

	UFUNCTION(BlueprintGetter, Category = Stat)
		float GetMaxHealth();

	UFUNCTION(BlueprintGetter, Category = Stat)
		float GetMaxEnergy();

	UFUNCTION(BlueprintGetter, Category = Stat)
		AActor* GetOtherActor();

	UFUNCTION(BlueprintSetter, Category = Stat)
		void SetHealth(float hp);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintSetter, Category = Stat)
		void SetEnergy(float en);

	UFUNCTION(BlueprintGetter, Category = Stat)
		EWeaponType GetCurrentWeapon();

	UFUNCTION(BlueprintSetter, Category = Stat)
		void SetCurrentWeapon(EWeaponType type);

	UFUNCTION(BlueprintSetter, Category = Stat)
		void SetOtherActor(AActor* actor);

	UFUNCTION(BlueprintGetter, Category = Instance)
		class UPlayerAnimInstance* GetPlayerAnimInstance();

private:

	void OnInteract();

	void DetectObject();



};