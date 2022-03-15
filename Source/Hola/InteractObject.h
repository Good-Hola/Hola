// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractObject.generated.h"

UCLASS()
class HOLA_API AInteractObject : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = Energy)
		int needEnergy;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* interactionSound;

	UPROPERTY(EditAnywhere, Category = Mesh)
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditInstanceOnly)
		class UWidgetComponent* widget;

public:
	// Sets default values for this actor's properties
	AInteractObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintGetter, Category = "Energy")
		float GetNeedEnergy();

	UFUNCTION(BlueprintNativeEvent)
		void Interact();

	virtual void SetWidgetStatus(bool status);
};