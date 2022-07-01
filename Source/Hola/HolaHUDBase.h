// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HolaHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class HOLA_API AHolaHUDBase : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
		class UUserWidget* CurrentWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> UserInterfaceWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> MainMenuWidget;

public:
	AHolaHUDBase();

	UFUNCTION()
		void DisplayMainMenuWidget();

	UFUNCTION()
		void DisplayUserInterfaceWidget();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<class UUserWidget> NewWidgetClass);
	
};
