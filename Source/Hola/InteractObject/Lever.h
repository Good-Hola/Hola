// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentObject.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Lever.generated.h"

UCLASS()
class HOLA_API ALever : public AParentObject, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractWithme() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	//	class USoundBase* openCloseSound;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	//	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Target)
		class TScriptInterface<IInteractionInterface> targetObj;

	// IInteractionInterface을(를) 통해 상속됨
	virtual void RequestInteract(APlayerCharacter* player) override;
};
