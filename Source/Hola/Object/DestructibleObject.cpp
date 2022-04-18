// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleObject.h"
#include "Components/BoxComponent.h"
#include "DestructibleComponent.h"
#include "Engine.h"

// Sets default values
ADestructibleObject::ADestructibleObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	
	mesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Mesh"));
	check(mesh);
	mesh->SetupAttachment(RootComponent);
	mesh->SetNotifyRigidBodyCollision(true);

	maxHp = 10.f;

}

// Called when the game starts or when spawned
void ADestructibleObject::BeginPlay()
{
	Super::BeginPlay();
	currentHp = maxHp;

	isDestroyed = false;
}

// Called every frame
void ADestructibleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UDestructibleComponent* ADestructibleObject::GetMesh()
{
	return mesh;
}


void ADestructibleObject::Destroy(float Damage, FVector HitLocation)
{
	if (!isDestroyed)
	{
		isDestroyed = true;
		mesh->ApplyRadiusDamage(Damage, HitLocation,
			ImpulseRadius, ImpulseStrength, true);
	}
}

float ADestructibleObject::TakeDamage(float Damage, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float retDmg = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	currentHp -= Damage;
	if (currentHp <= 0)
		Destroy(Damage, DamageCauser->GetActorLocation());
	return retDmg;
}

