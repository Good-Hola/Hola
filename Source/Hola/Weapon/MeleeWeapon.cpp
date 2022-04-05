#include "MeleeWeapon.h"
#include "Components/CapsuleComponent.h"

AMeleeWeapon::AMeleeWeapon()
{
	hitBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBox"));
	hitBox->SetupAttachment(RootComponent);
	hitBox->SetCollisionProfileName(TEXT("HolaWeapon"));
}

void AMeleeWeapon::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Warning, TEXT("in melee weapon"));
}
