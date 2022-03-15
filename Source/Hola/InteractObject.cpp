// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObject.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInteractObject::AInteractObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(mesh);
	RootComponent = mesh;
	mesh->SetCollisionObjectType(ECC_GameTraceChannel1);

	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	check(widget);
	widget->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AInteractObject::BeginPlay()
{
	Super::BeginPlay();
	widget->SetVisibility(false);
	//InputComponent->BindAction("Interact", IE_Pressed, this, &AInteractObject::Interact);
}

// Called every frame
void AInteractObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AInteractObject::GetNeedEnergy()
{
	return needEnergy;
}


void AInteractObject::Interact_Implementation()
{
	if (needEnergy > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("interact : %d"));
		UE_LOG(LogTemp, Log, TEXT("energy : %d"), needEnergy);
	}
}

void AInteractObject::SetWidgetStatus(bool status)
{
	widget->SetVisibility(status);
}