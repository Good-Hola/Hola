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
    *   저장해야 하는 것들
    *
    *   저장 당시 위치 (Location, Rotation)
    *   HP, Energy
    *   장착중인 무기 Melee, Ranged
    *   
    * 
    *   몬스터 위치정보 필요할까?
    *   InteractObject 정보 필요할까?
    * 
    */
	
};
