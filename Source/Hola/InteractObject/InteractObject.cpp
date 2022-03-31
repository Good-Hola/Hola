// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObject.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Character/PlayerCharacter.h"

// Sets default values
AInteractObject::AInteractObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	scene = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = scene;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(mesh);
	mesh->SetupAttachment(scene);
	mesh->SetCollisionObjectType(ECC_GameTraceChannel1);
	mesh->SetCollisionProfileName(TEXT("HolaObject"));

	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	check(widget);
	widget->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AInteractObject::BeginPlay()
{
	Super::BeginPlay();
	widget->SetVisibility(false);
	isAct = false;
}

int AInteractObject::GetNeedEnergy()
{
	return needEnergy;
}


void AInteractObject::Interact(APlayerCharacter* character)
{
	UE_LOG(LogTemp, Log, TEXT("is act : %d"), isAct);
	if (!isAct)
		TurnOn(character);
	else
		TurnOff(character);
}

void AInteractObject::TurnOn_Implementation(APlayerCharacter* character)
{
	if (character->GetEnergy() >= needEnergy)
	{
		isAct = !isAct;
		UE_LOG(LogTemp, Log, TEXT("Enough Energy"));
	}
	else
		UE_LOG(LogTemp, Log, TEXT("Not Enough Energy"));
	UE_LOG(LogTemp, Log, TEXT("Turn On"));
}

void AInteractObject::TurnOff_Implementation(APlayerCharacter* character)
{
	isAct = !isAct;
	UE_LOG(LogTemp, Log, TEXT("Turn Off"));
}

void AInteractObject::SetWidgetStatus(bool status)
{
	widget->SetVisibility(status);
}

UStaticMeshComponent* AInteractObject::GetMesh()
{
	return mesh;
}
