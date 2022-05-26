// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_HolaMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class HOLA_API APC_HolaMainMenu : public APlayerController
{
	GENERATED_BODY()
	
public:
	APC_HolaMainMenu();
	virtual void BeginPlay() override;

protected:
	virtual void SetupInputComponent() override;

	void EscapeKey();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UUMG_MainMenuBase> MainMenuUI;

	class UUMG_MainMenuBase* MainMenuUIObject;

};
