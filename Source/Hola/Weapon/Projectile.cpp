// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	projHitBox = CreateDefaultSubobject<USphereComponent>(TEXT("HitBox"));
	projHitBox->InitSphereRadius(10.0f);
	projHitBox->BodyInstance.SetCollisionProfileName("HolaProjectile");
	projHitBox->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	OnDestroyed.AddDynamic(this, &AProjectile::OnDestroyedProjectile);

	projHitBox->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	projHitBox->CanCharacterStepUpOn = ECB_No;

	RootComponent = projHitBox;

	projMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	projMesh->SetupAttachment(projHitBox);

	projParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	projParticle->bAutoActivate = false;
	projParticle->SetupAttachment(projHitBox);

	projMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	projMovement->UpdatedComponent = projHitBox;
	projMovement->InitialSpeed = 3000.f;
	projMovement->MaxSpeed = 3000.f;
	projMovement->bRotationFollowsVelocity = true;

	InitialLifeSpan = 3.0f;

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->GetClass()->IsChildOf(this->StaticClass()))
	{
		projHitBox->SetCollisionProfileName(TEXT("NoCollision"));
		projHitBox->SetGenerateOverlapEvents(false);
		projMesh->SetVisibility(false);

		projParticle->Activate();
		projParticle->DetachFromParent(true);
	}
}

void AProjectile::OnDestroyedProjectile(AActor* DestroyedActor)
{
	UE_LOG(LogTemp, Warning, TEXT("projectile destroyed"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector& direction)
{
	projMovement->Velocity = direction * projMovement->InitialSpeed;
}