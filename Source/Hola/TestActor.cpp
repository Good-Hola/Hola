// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = Scene;

	TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Test Mesh"));
	TestMesh->SetupAttachment(RootComponent);

	//OnActorBeginOverlap.AddDynamic(this, &ATestActor::OnBeginOverlap);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	InteractionWidget->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	InteractionWidget->SetVisibility(false);
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestActor::InteractWithme()
{
	//UE_LOG(LogTemp,Warning, TEXT("You have Interact With me!!"));	
	if (bIsOn)
	{
		//Already destroy
		bIsOn = false;
	}
	else
	{
		Destroy();
		bIsOn = true;
	}

	
	
}

void ATestActor::ShowInteractionWidget()
{
	InteractionWidget->SetVisibility(true);
}
void ATestActor::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}

//void ATestActor::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
//{
//	if (OtherActor && OtherActor->GetClass()->IsChildOf(AActor::StaticClass()))
//	{
//		OtherActor->basdf();
//	}
//}