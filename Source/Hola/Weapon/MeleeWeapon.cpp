#include "MeleeWeapon.h"
#include "../Character/PlayerAnimInstance.h"
#include "../Character/PlayerCharacter.h"
#include "../InteractObject/InteractObject.h"
#include "Components/CapsuleComponent.h"

AMeleeWeapon::AMeleeWeapon()
{
	hitBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBox"));
	hitBox->SetupAttachment(RootComponent);
	hitBox->SetCollisionProfileName(TEXT("HolaWeapon"));

	hitBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnBeginOverlap);

	isAttacking = false;
	currentCombo = 0;
	canHit = false;
}

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	maxCombo = comboSectionName.Num();
}

void AMeleeWeapon::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking = false;
	AttackEndComboState();

}

void AMeleeWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && canHit &&
		!OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("overlap actor"));
		// 공격을 한번 입이면 그 다음 공격은 안먹히도록 설정
		canHit = false;
	}
}


void AMeleeWeapon::AttackStartComboState()
{
	canNextCombo = true;
	isComboInputOn = false;
	currentCombo = FMath::Clamp<int32>(currentCombo + 1, 0, maxCombo - 1);
}

void AMeleeWeapon::AttackEndComboState()
{
	isComboInputOn = false;
	canNextCombo = false;
	currentCombo = 0;
	canHit = false;
}


void AMeleeWeapon::SetAnimInstance(UPlayerAnimInstance* instance)
{
	Super::SetAnimInstance(instance);
	animInstance->OnMontageEnded.AddDynamic(this, &AMeleeWeapon::OnAttackMontageEnded);
	animInstance->OnNextAttackCheck.AddLambda([this]() -> void {
		canNextCombo = false;
		if (isComboInputOn)
		{
			animInstance->Montage_JumpToSection(FName(comboSectionName[currentCombo]));
			AttackStartComboState();
		}
		});
	animInstance->OnAttackHitCheck.AddLambda([this]() -> void {
		canHit = true;
	});
}

void AMeleeWeapon::Attack()
{
	if (animInstance && attackMontage)
	{
		if (isAttacking)
		{
			if (canNextCombo)
				isComboInputOn = true;
		}
		else
		{
			animInstance->Montage_Play(attackMontage);
			animInstance->Montage_JumpToSection(FName(comboSectionName[currentCombo]));
			AttackStartComboState();
			isAttacking = true;
		}
	}

}

