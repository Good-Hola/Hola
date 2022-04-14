#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class HOLA_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class UCapsuleComponent* hitBox;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool isAttacking;

	UPROPERTY(EditDefaultsOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* attackMontage;

	bool canNextCombo;

	bool isComboInputOn;

	UPROPERTY(EditDefaultsOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		TArray<FString> comboSectionName;

	int32 maxCombo;
	
	int32 currentCombo;

	bool canHit;
private:

	void AttackStartComboState();

	void AttackEndComboState();

protected:
	virtual	void BeginPlay() override;

public:
	AMeleeWeapon();

	virtual void Attack() override;

	virtual void SetAnimInstance(class UPlayerAnimInstance* instance) override;

	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};