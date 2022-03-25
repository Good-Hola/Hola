// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS(abstract)
class HOLA_API AProjectile : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* projHitBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* projParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* projMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* projMovement;

public:
	// Sets default values for this actor's properties
	AProjectile();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector NormalImpulse,
			const FHitResult& Hit);

	UFUNCTION()
		void OnDestroyedProjectile(AActor* DestroyedActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};