// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractObject.generated.h"

UCLASS()
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
		class USoundBase* interactionSound;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditInstanceOnly)
		class UWidgetComponent* widget;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintGetter, Category = "Energy")
		int GetNeedEnergy();

	UFUNCTION(BlueprintNativeEvent)
		void Interact();

	virtual void SetWidgetStatus(bool status);
};