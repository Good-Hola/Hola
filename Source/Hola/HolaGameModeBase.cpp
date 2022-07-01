// Copyright Epic Games, Inc. All Rights Reserved.


#include "HolaGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "PC_HolaMainMenu.h"
#include "Character/HolaPlayerController.h"
#include "HolaHUDBase.h"

AHolaGameModeBase::AHolaGameModeBase()
{
	PlayerControllerClass = AHolaPlayerController::StaticClass();
}

void AHolaGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
