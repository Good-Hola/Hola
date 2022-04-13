// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleObject.generated.h"

UCLASS()
class HOLA_API ADestructibleObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destructible, meta = (AllowPrivateAccess = "true"))
	class UDestructibleComponent* mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible, meta = (AllowPrivateAccess = "true"))
	float maxHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destructible, meta = (AllowPrivateAccess = "true"))
	float currentHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destructible, meta = (AllowPrivateAccess = "true"))
	bool isDestroyed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Destructible, meta = (AllowPrivateAccess = "true"))
		float ImpulseRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Destructible, meta = (AllowPrivateAccess = "true"))
		float ImpulseStrength;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UDestructibleComponent* GetMesh();

	UFUNCTION()
	void Destroy(float Damage, FVector HitLocation);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;



};
