// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class HOLA_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString SaveSlotName;       // Save game data file name

    UPROPERTY(VisibleAnywhere, Category = Basic)
        uint32 SaveIndex;           // Save game data file index

    /*
    *   �����ؾ� �ϴ� �͵�
    *
    *   ���� ��� ��ġ (Location, Rotation)
    *   HP, Energy
    *   �������� ���� Melee, Ranged
    *   
    * 
    *   ���� ��ġ���� �ʿ��ұ�?
    *   InteractObject ���� �ʿ��ұ�?
    * 
    */
	
};
