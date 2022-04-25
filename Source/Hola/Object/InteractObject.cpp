// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObject.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Character/PlayerCharacter.h"

// Sets default values
AInteractObject::AInteractObject()
{
	PrimaryActorTick.bCanEverTick = true;

	scene = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = scene;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(mesh);
	mesh->SetupAttachment(scene);
	mesh->SetCollisionObjectType(ECC_GameTraceChannel1);
	mesh->SetCollisionProfileName(TEXT("HolaObject"));

	/*
	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	check(widget);
	widget->SetupAttachment(RootComponent);
	*/
}

// Called when the game starts or when spawned
void AInteractObject::BeginPlay()
{
	Super::BeginPlay();
	//widget->SetVisibility(false);
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
		character->SetEnergy(character->GetEnergy() - needEnergy);
	}
}

void AInteractObject::TurnOff_Implementation(APlayerCharacter* character)
{
	isAct = !isAct;
	character->SetEnergy(character->GetEnergy() + needEnergy);
}

UStaticMeshComponent* AInteractObject::GetMesh()
{
	return mesh;
}
