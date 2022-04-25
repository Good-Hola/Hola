// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObject.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
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

bool AInteractObject::GetIsAct()
{
	return isAct;
}

void AInteractObject::SetIsAct(bool status)
{
	isAct = status;
}

void AInteractObject::TurnOn_Implementation(APlayerCharacter* character)
{
	if (character->GetEnergy() >= needEnergy)
	{
		isAct = !isAct;
		character->SetEnergy(character->GetEnergy() - needEnergy);
		if (turnOnSound)
			UGameplayStatics::PlaySoundAtLocation(this, turnOnSound, GetActorLocation());
	}
}

void AInteractObject::TurnOff_Implementation(APlayerCharacter* character)
{
	isAct = !isAct;
	character->SetEnergy(character->GetEnergy() + needEnergy);
	if (turnOffSound)
		UGameplayStatics::PlaySoundAtLocation(this, turnOffSound, GetActorLocation());
}

FString AInteractObject::GetObjectDescription()
{
	return ObjectDescription;
}

UStaticMeshComponent* AInteractObject::GetMesh()
{
	return mesh;
}
