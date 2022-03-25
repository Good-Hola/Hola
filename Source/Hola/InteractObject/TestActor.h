// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "Components/WidgetComponent.h"
#include "TestActor.generated.h"

UCLASS()
class HOLA_API ATestActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()	
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void InteractWithme() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

	//UFUNCTION()
	//void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	//APlayerCharacter* player;

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* Scene;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TestMesh;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* InteractionWidget;

	bool bIsOn = false;

	// IInteractionInterface을(를) 통해 상속됨
	virtual void RequestInteract(APlayerCharacter* player) override;
};
