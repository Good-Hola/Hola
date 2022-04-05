#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "RangedWeapon.generated.h"

UCLASS()
class HOLA_API ARangedWeapon : public AWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> projectile;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		class USceneComponent* projSpawn;

public:
	ARangedWeapon();

	virtual void Attack() override;

};