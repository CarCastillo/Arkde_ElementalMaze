// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_OrbProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "EM_Character.h"
#include "DrawDebugHelpers.h"
#include "EM_Weapon.h"

// Sets default values
AEM_OrbProjectile::AEM_OrbProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OrbDamage = 100.f;
	OrbExplodeDelay = 3.0f;
	OrbDestroyDelay = 0.3f;

	OrbProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("OrbProjectileCollision"));
	RootComponent = OrbProjectileCollision;

	OrbProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbProjectileMesh"));
	OrbProjectileMesh->SetupAttachment(RootComponent);

	OrbProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	OrbProjectileMovementComponent->InitialSpeed = 1500.0f;
	OrbProjectileMovementComponent->MaxSpeed = 1500.0f;
}

// Called when the game starts or when spawned
void AEM_OrbProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(OrbExplodeTimer, this, &AEM_OrbProjectile::ExplodeOrbProjectile, OrbExplodeDelay, true);
}

void AEM_OrbProjectile::ExplodeOrbProjectile()
{
	OrbProjectileMesh->SetRelativeScale3D(FVector(8, 8, 8));
	DrawDebugSphere(GetWorld(), OrbProjectileMesh->GetComponentLocation(), 150.0f, 32, FColor::Blue, false, 2.0f);
	UGameplayStatics::SpawnEmitterAttached(ExplodeEffect, OrbProjectileMesh);
	GetWorldTimerManager().SetTimer(OrbDestroyTimer, this, &AEM_OrbProjectile::DestroyOrbProjectile, OrbDestroyDelay, true);
}

void AEM_OrbProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor) && OtherActor != OwnerWeapon)
	{
		AEM_Weapon* Weapon = Cast<AEM_Weapon>(OwnerWeapon);

		if (IsValid(Weapon))
		{
			if (Weapon->GetCharacterOwner() != OtherActor)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "DAMAGE ENEMY!");
				UGameplayStatics::ApplyRadialDamage(GetWorld(), OrbDamage, GetActorLocation(), 150.0f, DamageType, TArray<AActor*>(), this, Weapon->GetCharacterOwner()->GetInstigatorController(), true, ECC_Visibility);
				ExplodeOrbProjectile();
			}
		}
	}
}

void AEM_OrbProjectile::DestroyOrbProjectile()
{
	GetWorldTimerManager().ClearTimer(OrbExplodeTimer);
	Destroy();
}

// Called every frame
void AEM_OrbProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

