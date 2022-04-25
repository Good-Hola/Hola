// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractObject.generated.h"

UCLASS(abstract)
class HOLA_API AInteractObject : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	AInteractObject();

protected:

	UPROPERTY(EditAnywhere, BlueprintGetter = GetNeedEnergy, Category = Energy)
		int needEnergy;

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "flag")
		bool isAct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Scene)
		class USceneComponent* scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
		class USoundCue* turnOnSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
		class USoundCue* turnOffSound;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetObjectDescription, BlueprintReadWrite, Category = Description)
		FString ObjectDescription;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* mesh;

	/*
	UPROPERTY(EditInstanceOnly)
		class UWidgetComponent* widget;
	*/
public:

	UFUNCTION(BlueprintGetter, Category = "Energy")
		int GetNeedEnergy();

	void Interact(class APlayerCharacter* character);

	UFUNCTION(BlueprintNativeEvent)
		void TurnOn(class APlayerCharacter* character);
	virtual void TurnOn_Implementation(class APlayerCharacter* character);

	UFUNCTION(BlueprintNativeEvent)
		void TurnOff(class APlayerCharacter* character);
	virtual void TurnOff_Implementation(class APlayerCharacter* character);

	UFUNCTION(BlueprintGetter, Category = Description)
		FString GetObjectDescription();

	UFUNCTION()
	class UStaticMeshComponent* GetMesh();
};