// Fill out your copyright notice in the Description page of Project Settings.


#include "HolaHUDBase.h"
#include "Blueprint/UserWidget.h"

AHolaHUDBase::AHolaHUDBase()
{
}

void AHolaHUDBase::DisplayMainMenuWidget()
{
	ChangeMenuWidget(MainMenuWidget);
}

void AHolaHUDBase::DisplayUserInterfaceWidget()
{
	ChangeMenuWidget(UserInterfaceWidget);
}

void AHolaHUDBase::BeginPlay()
{
	Super::BeginPlay();
}

void AHolaHUDBase::ChangeMenuWidget(TSubclassOf<class UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
