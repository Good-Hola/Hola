// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentWeapon.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AParentWeapon::AParentWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	weapon->SetupAttachment(RootComponent);

	weapon->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AParentWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	capsule->OnComponentBeginOverlap.AddDynamic(this, &AParentWeapon::OnBeginOverlap);
	capsule->OnComponentEndOverlap.AddDynamic(this, &AParentWeapon::OnEndOverlap);

}

// Called every frame
void AParentWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParentWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;

	UGameplayStatics::ApplyDamage(OtherActor, damage, nullptr, GetOwner(), nullptr);

}

void AParentWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

