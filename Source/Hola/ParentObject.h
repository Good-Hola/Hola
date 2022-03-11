// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParentObject.generated.h"

UCLASS()
class HOLA_API AParentObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
		class USoundBase* interactionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* meshComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
		int needEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interact)
		bool isActive;
};
