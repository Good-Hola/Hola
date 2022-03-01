// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interaction.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class HOLA_API ADoor : public AActor, public IInteraction
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

	void DoorToggle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
		USoundBase* openCloseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* meshComp;

private:
	bool isOpen;

	// IInteraction을(를) 통해 상속됨
	virtual void Interaction(APlayerCharactor* charactor) override;

	void OnOverlapBegin(UPrimitiveComponent* overrlapedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIdx, bool fromSweep, const FHitResult& sweepResult);

};
