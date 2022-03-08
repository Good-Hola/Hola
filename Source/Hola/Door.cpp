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
	meshComp->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);

}

void ADoor::DoorToggle()
{
	UGameplayStatics::PlaySoundAtLocation(this, openCloseSound, AActor::GetActorLocation());

	if (isOpen)
	{
		// Play Open Animation
	}
	else
	{
		// Play Close Animation
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

void ADoor::OnOverlapBegin(UPrimitiveComponent* overrlapedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIdx, bool fromSweep, const FHitResult& sweepResult)
{
	UE_LOG(LogCollision, Log, TEXT("OnOverlapBegin"));

}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::Interaction(APlayerCharactor* charactor)
{
	DoorToggle();

}

