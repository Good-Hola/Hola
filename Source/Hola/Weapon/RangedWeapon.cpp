// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "../Character/PlayerCharacter.h"

ARangedWeapon::ARangedWeapon()
{
	projSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjtileSpawn"));
	projSpawn->SetupAttachment(RootComponent);
}

void ARangedWeapon::Attack()
{
    if (projectile)
    {
        if (GetWorld())
        {
            const APlayerCharacter* const ownerPlayer = Cast<APlayerCharacter>(GetOwner());
            if (ownerPlayer == nullptr)
                return;

            const UCameraComponent* const ownerCamera = ownerPlayer->GetFollowCamera();
            if (ownerCamera == nullptr)
                return;

            const FVector start = ownerCamera->GetComponentLocation();
            const FVector end = start + ownerCamera->GetComponentQuat().GetForwardVector() * 1000.0f;

            FHitResult hit;

            const bool isHit = GetWorld()->LineTraceSingleByChannel(
                hit, start, end, ECollisionChannel::ECC_Visibility);

            const FVector hitLocation = isHit ? hit.Location : end;

            const FVector direction = FVector(hitLocation - ownerPlayer->GetActorLocation()).GetSafeNormal();

            AProjectile* newPjtl = GetWorld()->SpawnActor<AProjectile>(projectile,
                projSpawn->GetComponentLocation(), projSpawn->GetComponentRotation());

            if (newPjtl == nullptr)
                return;

            newPjtl->FireInDirection(direction);
        }
    }
}
