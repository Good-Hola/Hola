// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetupAttachment(RootComponent);
}

void ADoor::DoorToggle()
{
	UGameplayStatics::PlaySoundAtLocation(this, interactionSound, AActor::GetActorLocation());

	if (isOpen)
	{
		// Play Open Animation
		UE_LOG(LogCollision, Log, TEXT("Door Close"));
	}
	else
	{
		// Play Close Animation
		UE_LOG(LogCollision, Log, TEXT("Door Open"));
	}

	isOpen = !isOpen;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

}

void ADoor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::InteractWithme()
{
	DoorToggle();
}

void ADoor::ShowInteractionWidget()
{
}

void ADoor::HideInteractionWidget()
{
}


