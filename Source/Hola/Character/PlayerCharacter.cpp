// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "../InteractObject/TestWeapon.h"
#include "../InteractObject/InteractObject.h"
#include "../InteractObject/InteractWeapon.h"
#include "../Weapon/Weapon.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
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

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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
		return ;
	UE_LOG(LogTemp, Log, TEXT("nums : %d"), OverlappingActors.Num());

	AActor* Closest = OverlappingActors[0];
	for (auto CurrentActor : OverlappingActors)
	{
		if (GetDistanceTo(CurrentActor) < GetDistanceTo(Closest))
		{
			Cast<AInteractObject>(Closest)->SetWidgetStatus(false);
			Closest = CurrentActor;
		}
	}

	focusedActor = Cast<AInteractObject>(Closest);
	focusedActor->SetWidgetStatus(true);

}

void APlayerCharacter::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		DetectObject();
	}
}

void APlayerCharacter::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AInteractObject* obj = Cast<AInteractObject>(OtherActor);
	if (obj && obj == focusedActor)
	{
		obj->SetWidgetStatus(false);
		focusedActor = nullptr;
		DetectObject();
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

void APlayerCharacter::SetHealth(float hp)
{
	health = hp;
}

void APlayerCharacter::SetEnergy(float en)
{
	energy = en;
}

void APlayerCharacter::OnInteract()
{
	// InteractWeapon인지 아닌지 체크
	if (focusedActor)
	{
		focusedActor->Interact(this);
	}
}

bool APlayerCharacter::CanSetWeapon()
{
	return nullptr == currentWeapon;
}

void APlayerCharacter::SetWeapon(AWeapon* newWeapon)
{
	UE_LOG(LogTemp, Log, TEXT("Set Set"));

}



	/*
	if (nullptr != NewWeapon && nullptr == currentWeapon)
		UE_LOG(LogTemp, Log, TEXT("Can't equip weapon"));
	FName WeaponSocket(TEXT("hand_rSocket"));
	if (NewWeapon != nullptr)
	{
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		NewWeapon->AddActorLocalRotation(FQuat(0.f, 0.f, 0.f, 93.f));
		currentWeapon = NewWeapon;
	}
	*/
