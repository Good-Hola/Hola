// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HolaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HOLA_API AHolaPlayerController: public APlayerController
{
	GENERATED_BODY()


public:
	AHolaPlayerController();
	virtual void BeginPlay() override;

protected:
	virtual void SetupInputComponent() override;


	void EscapeKey();

	void TestKey();

public:
	
};
