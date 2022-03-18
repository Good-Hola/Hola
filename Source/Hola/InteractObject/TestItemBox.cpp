// Fill out your copyright notice in the Description page of Project Settings.

#include "TestItemBox.h"
#include "../Character/PlayerCharacter.h"
#include "TestWeapon.h"
#include "Components/BoxComponent.h"

// Sets default values
ATestItemBox::ATestItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponItemClass = ATestWeapon::StaticClass();
}

void ATestItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATestItemBox::OnCharacterOverlap);
}

// Called when the game starts or when spawned
void ATestItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Warning"));
	auto Character = Cast<APlayerCharacter>(OtherActor);

	if (Character != nullptr && WeaponItemClass != nullptr)
	{
		if (Character->CanSetWeapon())
		{
			auto NewWeapon = GetWorld()->SpawnActor<ATestWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			Character->SetWeapon(NewWeapon);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Already equiped"));
		}
	}
}