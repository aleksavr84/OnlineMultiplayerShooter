// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileGrenade.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AProjectileGrenade::AProjectileGrenade()
{
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Greanade Mesh"));
    ProjectileMesh->SetupAttachment(RootComponent);
    ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->SetIsReplicated(true);
    ProjectileMovementComponent->bShouldBounce = true;
}

void AProjectileGrenade::BeginPlay()
{
    AActor::BeginPlay();

    StartDestroyTimer();
    SpawnTrailSystem();

    ProjectileMovementComponent->OnProjectileBounce.AddDynamic(this, &AProjectileGrenade::OnBounce);
}

void AProjectileGrenade::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
    AActor* HitActor = ImpactResult.GetActor();

    //UE_LOG(LogTemp, Warning, TEXT("%s"), *HitActor->GetName());

    if (BounceSound)
    {
        UGameplayStatics::PlaySoundAtLocation(
            this,
            BounceSound,
            GetActorLocation()
        );
    }
}

void AProjectileGrenade::Destroyed()
{
    ExplodeDamage();
    Super::Destroyed();
}
