// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Gripable.generated.h"

class APlayerCharactor;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGripable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HOLA_API IGripable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Grip(APlayerCharactor* charactor) = 0;
};
