// Fill out your copyright notice in the Description page of Project Settings.


#include "Lever.h"

// Sets default values
ALever::ALever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALever::InteractWithme()
{
	//targetObj->InteractWithme();

}

void ALever::ShowInteractionWidget()
{
}

void ALever::HideInteractionWidget()
{
}

void ALever::RequestInteract(APlayerCharacter* player)
{
}
