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

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetHealth, BlueprintSetter = SetHealth, Category = Stat)
		float health;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetEnergy, BlueprintSetter = SetEnergy, Category = Stat)
		float energy;
	UPROPERTY(BlueprintGetter = GetOtherActor, BlueprintSetter = SetOtherActor, Category = Stat)
		AActor* TakeOtherActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

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

	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCurrentStage, BlueprintSetter = SetCurrentStage, Category = Stage)
		int currentStage;

public:
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	FSwapWeaponDelegate SwapWeaponDelegate;

	UFUNCTION(BlueprintNativeEvent)
		void Death();
	virtual void Death_Implementation();

protected:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual	void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void SwapWeapon(EWeaponType type);

	void Attack();

	void DropWeapon();


public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

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

	UFUNCTION(BlueprintGetter, Category = Instance)
		int GetCurrentStage();

	UFUNCTION(BlueprintSetter, Category = Instance)
		void SetCurrentStage(int stage);

private:

	void OnInteract();

	void DetectObject();



};