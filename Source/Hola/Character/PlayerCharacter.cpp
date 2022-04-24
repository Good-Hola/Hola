// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
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

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->SetCollisionProfileName("HolaCharacter");
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_GameTraceChannel4);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	//GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->CrouchedHalfHeight = 60.0f;


	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 200.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

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
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::StartCrouch);
	//PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::StopCrouch);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::OnInteract);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
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
	health = max_hp;
	energy = max_energy;

	widget->SetVisibility(false);
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
		//if (weapon[(int)currentWeaponIndex + 1 % (int)EWeaponType::MAX_COUNT])
			//SetCurrentWeapon()
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

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Hi"));
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
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

//void APlayerCharacter::StartCrouch()
//{
//	GetCharacterMovement()->bWantsToCrouch = true;
//	isCrouching = true;
//}

//void APlayerCharacter::StopCrouch()
//{
//	GetCharacterMovement()->bWantsToCrouch = false;
//	isCrouching = false;
//}


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
