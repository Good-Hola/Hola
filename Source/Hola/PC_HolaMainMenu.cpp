// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_HolaMainMenu.h"
#include "Widgets/UMG_MainMenuBase.h"
#include "Engine/GameEngine.h"

APC_HolaMainMenu::APC_HolaMainMenu()
{

}

void APC_HolaMainMenu::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuUI)
	{
		MainMenuUIObject = CreateWidget<UUMG_MainMenuBase>(this, MainMenuUI);
		MainMenuUIObject->AddToViewport();
		MainMenuUIObject->ShowUpAnim();
	}

	SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());
}

void APC_HolaMainMenu::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("Exit", IE_Pressed, this, &APC_HolaMainMenu::EscapeKey);
	}
}

void APC_HolaMainMenu::EscapeKey()
{
	if (MainMenuUIObject)
	{
		if (MainMenuUIObject->GetIsExitMenuOn())
		{
			MainMenuUIObject->HideExitMenu();
		}
		else
		{
			MainMenuUIObject->DisplayExitMenu();
		}
	}

}
