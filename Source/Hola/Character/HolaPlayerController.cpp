// Fill out your copyright notice in the Description page of Project Settings.


#include "HolaPlayerController.h"
#include "../Widgets/UMG_MainMenuBase.h"
#include "Engine/GameEngine.h"


AHolaPlayerController::AHolaPlayerController()
{

}

void AHolaPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AHolaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("Exit", IE_Pressed, this, &AHolaPlayerController::EscapeKey);
		InputComponent->BindKey(EKeys::O, IE_Pressed, this, &AHolaPlayerController::TestKey);
	}
}

void AHolaPlayerController::EscapeKey()
{

}

void AHolaPlayerController::TestKey()
{
	UE_LOG(LogTemp, Warning, TEXT("HolaPlayerController Press O Key"));
}