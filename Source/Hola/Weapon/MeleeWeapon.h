#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "MeleeWeapon.generated.h"

/**
 *
 */
UCLASS()
class HOLA_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class UCapsuleComponent* hitBox;



public:
	AMeleeWeapon();

	virtual void Attack() override;

protected:


};