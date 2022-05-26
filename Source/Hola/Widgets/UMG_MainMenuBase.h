// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG_MainMenuBase.generated.h"

/**
 * 
 */
UCLASS()
class HOLA_API UUMG_MainMenuBase : public UUserWidget
{
	GENERATED_BODY()

private:
	bool IsExitMenuOn;

protected:
	UPROPERTY(Meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* ShowUp;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
		class UOverlay* MenuBoxOverlay;

	UPROPERTY(Meta = (BindWidget))
		class UVerticalBox* MenuVerticalBox;

	UPROPERTY(Meta = (BindWidget))
		class UButton* Btn_NewGame;

	UPROPERTY(Meta = (BindWidget))
		class UButton* Btn_LoadGame;

	UPROPERTY(Meta = (BindWidget))
		class UButton* Btn_Option;

	UPROPERTY(Meta = (BindWidget))
		class UButton* Btn_Quit;

	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* ExitQuesBox;

	UPROPERTY(Meta = (BindWidget))
		class UButton* Btn_ExitAgree;

	UPROPERTY(Meta = (BindWidget))
		class UButton* Btn_ExitDeny;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClickedNewGame();

	UFUNCTION()
		void OnClickedLoadGame();

	UFUNCTION()
		void OnClickedOption();

	UFUNCTION()
		void OnClickedQuitGame();

	UFUNCTION()
		void OnClickedExitAgree();

	UFUNCTION()
		void OnClickedExitDeny();


public:
	void ShowUpAnim();

	bool GetIsExitMenuOn();

	UFUNCTION()
		void DisplayExitMenu();

	UFUNCTION()
		void HideExitMenu();

	
};
