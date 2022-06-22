// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG_MainMenuBase.h"
#include "Components/Overlay.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../PC_HolaMainMenu.h"

void UUMG_MainMenuBase::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_NewGame->OnClicked.AddDynamic(this, &UUMG_MainMenuBase::OnClickedNewGame);
	Btn_LoadGame->OnClicked.AddDynamic(this, &UUMG_MainMenuBase::OnClickedLoadGame);
	Btn_Option->OnClicked.AddDynamic(this, &UUMG_MainMenuBase::OnClickedOption);
	Btn_Quit->OnClicked.AddDynamic(this, &UUMG_MainMenuBase::OnClickedQuitGame);
	Btn_ExitAgree->OnClicked.AddDynamic(this, &UUMG_MainMenuBase::OnClickedExitAgree);
	Btn_ExitDeny->OnClicked.AddDynamic(this, &UUMG_MainMenuBase::OnClickedExitDeny);

	Btn_NewGame->bIsVariable = true;

	ExitQuesBox->SetVisibility(ESlateVisibility::Collapsed);

	ShowUpAnim();
}

void UUMG_MainMenuBase::ShowUpAnim()
{
	PlayAnimation(ShowUp);
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("cjeclk"));
}

bool UUMG_MainMenuBase::GetIsExitMenuOn()
{
	return IsExitMenuOn;
}

void UUMG_MainMenuBase::DisplayExitMenu()
{
	IsExitMenuOn = true;
	ExitQuesBox->SetVisibility(ESlateVisibility::Visible);
}

void UUMG_MainMenuBase::HideExitMenu()
{
	IsExitMenuOn = false;
	ExitQuesBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UUMG_MainMenuBase::OnClickedNewGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("New Game"));
	
	APC_HolaMainMenu* controller = Cast<APC_HolaMainMenu>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetInputMode(FInputModeGameOnly());
	controller->SetShowMouseCursor(false);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Level_Stage1"));
}

void UUMG_MainMenuBase::OnClickedLoadGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("Load Game"));

}

void UUMG_MainMenuBase::OnClickedOption()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("Option"));
}

void UUMG_MainMenuBase::OnClickedQuitGame()
{
	DisplayExitMenu();
}

void UUMG_MainMenuBase::OnClickedExitAgree()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UUMG_MainMenuBase::OnClickedExitDeny()
{
	HideExitMenu();
}

