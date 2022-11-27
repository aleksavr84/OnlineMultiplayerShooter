// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileRocket.h"
#include "Kismet/GameplayStatics.h"

AProjectileRocket::AProjectileRocket()
{
    RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket Mesh"));
    RocketMesh->SetupAttachment(RootComponent);
    RocketMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AProjectileRocket::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

    APawn* FiringPawn = GetInstigator();

    if (FiringPawn)
    {
        AController* FiringController = FiringPawn->GetController();

        if (FiringController)
        {
            UGameplayStatics::ApplyRadialDamageWithFalloff(
                this, // World context object
                Damage, // BaseDamage
                10.f, // MinimumDamage
                GetActorLocation(), // Origin
                200.f, // Damage inner raduis
                500.f, // Damage outer radius
                1.f, // Damage falloff
                UDamageType::StaticClass(), // DamageType class
                TArray<AActor*>(), // Ignore actors
                this, // Damage causer
                FiringController // Instigator controller
            );
        }
    }

    Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}