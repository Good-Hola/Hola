// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "../Object/InteractObject.h"
#include "../Object/InteractWeapon.h"
#include "../Weapon/Weapon.h"
#include "PlayerAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->SetCollisionProfileName("HolaCharacter");
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_GameTraceChannel4);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->CrouchedHalfHeight = 60.0f;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(60.f, 96.0f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnTriggerBeginOverlap);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnTriggerEndOverlap);

	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	check(widget);
	widget->SetupAttachment(FollowCamera);

}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::OnInteract);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction<FSwapWeaponDelegate>("GripSword", IE_Pressed,
		this, &APlayerCharacter::SwapWeapon, EWeaponType::MELEE);
	PlayerInputComponent->BindAction<FSwapWeaponDelegate>("GripGun", IE_Pressed, this, &APlayerCharacter::SwapWeapon, EWeaponType::RANGED);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction("DropWeapon", IE_Pressed, this, &APlayerCharacter::DropWeapon);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (health == -1)
		health = max_hp;
	if (energy == -1)
		energy = max_energy;

	widget->SetVisibility(false);
	currentStage = 1;
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	animInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	SetCurrentWeapon(EWeaponType::MAX_COUNT);
	animInstance->SetCurrentWeaponType(EWeaponType::MAX_COUNT);
	SwapWeaponDelegate.BindUFunction(this, "SwapWeapon");

	weapon.Init(nullptr, 2);
}

void APlayerCharacter::SwapWeapon(EWeaponType type)
{
	if (weapon[(int)type] == nullptr)
		return;

	FName WeaponSocket;
	if (currentWeaponIndex == type)
	{
		WeaponSocket = FName(*(weapon[(int)type]->GetBackSocketName()));
		// grip 애니메이션을 실행
		// 현재 문제점 : 애니메이션 실행과 동시에 소켓 연결이 일어나서 
		//				넣는 동안 손에 들고있어야하는데 바로 등으로 붙어버림
		// 델리게이트로 애니메이션 끝나고 실행하려면 type 변수와 WeaponSocket 변수를 넘겨줘야
		// 하는데 자체 델리게이트로는 변수 전달이 불가능
		weapon[(int)type]->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		SetCurrentWeapon(EWeaponType::MAX_COUNT);
	}
	else if (currentWeaponIndex != type)
	{
		if (((int)type + 1) % (int)EWeaponType::MAX_COUNT == (int)currentWeaponIndex)
		{
			WeaponSocket = FName(*(weapon[(int)currentWeaponIndex])->GetBackSocketName());
			weapon[(int)currentWeaponIndex]->AttachToComponent(GetMesh(),
				FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		}
		WeaponSocket = FName(*(weapon[(int)type]->GetHoldSocketName()));
		weapon[(int)type]->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		animInstance->Montage_Play(weapon[(int)type]->GetGripAnimMontage());
		animInstance->Montage_JumpToSection(FName(*(weapon[(int)type])->GetGripAnimSectionName()),
			weapon[(int)type]->GetGripAnimMontage());
		SetCurrentWeapon(type);
	}
}

void APlayerCharacter::Attack()
{
	if (currentWeaponIndex < EWeaponType::MAX_COUNT && weapon[(int)currentWeaponIndex])
	{
		weapon[(int)currentWeaponIndex]->Attack();
	}
}

void APlayerCharacter::DropWeapon()
{
	if (currentWeaponIndex != EWeaponType::MAX_COUNT && weapon[(int)currentWeaponIndex])
	{
		weapon[(int)currentWeaponIndex]->SpawnInteractWeapon(this);
		weapon[(int)currentWeaponIndex] = nullptr;
		SetCurrentWeapon(EWeaponType::MAX_COUNT);
	}
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerCharacter::DetectObject()
{
	TArray<AActor*>OverlappingActors;

	TriggerCapsule->GetOverlappingActors(OverlappingActors, AInteractObject::StaticClass());

	if (OverlappingActors.Num() == 0)
		return;
	AActor* Closest = OverlappingActors[0];
	for (auto CurrentActor : OverlappingActors)
	{
		if (GetDistanceTo(CurrentActor) < GetDistanceTo(Closest))
		{
			Closest = CurrentActor;
		}
	}

	focusedActor = Cast<AInteractObject>(Closest);

}

void APlayerCharacter::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && !OtherActor->GetClass()->IsChildOf(this->StaticClass()))
	{
		DetectObject();
		if(OtherActor->GetClass()->IsChildOf(AInteractObject::StaticClass()))
			widget->SetVisibility(true);
		TakeOtherActor = OtherActor;
	}
}

void APlayerCharacter::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AInteractObject* obj = Cast<AInteractObject>(OtherActor);
	if (obj && obj == focusedActor)
	{
		focusedActor = nullptr;
		DetectObject();
		if (OtherActor->GetClass()->IsChildOf(AInteractObject::StaticClass()))
			widget->SetVisibility(false);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

float APlayerCharacter::GetHealth()
{
	return health;
}


float APlayerCharacter::GetEnergy()
{
	return energy;
}

float APlayerCharacter::GetMaxHealth()
{
	return max_hp;
}

float APlayerCharacter::GetMaxEnergy()
{
	return max_energy;
}
AActor* APlayerCharacter::GetOtherActor()
{
	return TakeOtherActor;
}

void APlayerCharacter::SetHealth(float hp)
{
	health = hp;
	if (health > max_hp)
		health = max_hp;
}

void APlayerCharacter::SetOtherActor(AActor* actor)
{
	TakeOtherActor = actor;
}

void APlayerCharacter::Death_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("character is dead"));
	for (auto& curWeapon : weapon)
	{
		if (curWeapon != nullptr)
		{
			currentWeaponIndex = curWeapon->GetWeaponType();
			DropWeapon();
		}
	}
}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	health -= damage;
	if (health > max_hp)
		health = max_hp;
	if (health <= 0)
		Death();
	return damage;
}

void APlayerCharacter::SetEnergy(float en)
{
	energy = en;
	if (energy > max_energy)
		energy = max_energy;
}

EWeaponType APlayerCharacter::GetCurrentWeapon()
{
	return currentWeaponIndex;
}

void APlayerCharacter::SetCurrentWeapon(EWeaponType type)
{
	currentWeaponIndex = type;
	animInstance->SetCurrentWeaponType(type);
}

UPlayerAnimInstance* APlayerCharacter::GetPlayerAnimInstance()
{
	return animInstance;
}

int APlayerCharacter::GetCurrentStage()
{
	return currentStage;
}

void APlayerCharacter::SetCurrentStage(int stage)
{
	currentStage = stage;
}

void APlayerCharacter::OnInteract()
{
	if (focusedActor)
	{
		focusedActor->Interact(this);
	}
}

void APlayerCharacter::SetWeapon(AWeapon* newWeapon)
{
	if (newWeapon)
	{
		FName WeaponSocket;
		if (currentWeaponIndex != EWeaponType::MAX_COUNT && currentWeaponIndex != newWeapon->GetWeaponType())
		{
			WeaponSocket = FName(*(weapon[(int)currentWeaponIndex]->GetBackSocketName()));
			weapon[(int)currentWeaponIndex]->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		}
		SetCurrentWeapon(newWeapon->GetWeaponType());
		WeaponSocket = FName(*(newWeapon->GetHoldSocketName()));
		newWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		newWeapon->SetOwner(this);
		if (weapon[(int)currentWeaponIndex])
			weapon[(int)currentWeaponIndex]->SpawnInteractWeapon(this);
		weapon[(int)currentWeaponIndex] = newWeapon;
		weapon[(int)currentWeaponIndex]->SetAnimInstance(animInstance);
	}
}
