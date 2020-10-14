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

// Sets default values
AEM_OrbProjectile::AEM_OrbProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "EXPLODE ORB!");
	// OrbProjectileMesh->SetRelativeScale3D(FVector(8, 8, 8));
	DrawDebugSphere(GetWorld(), OrbProjectileMesh->GetComponentLocation(), 150.0f, 32, FColor::Blue, false, 2.0f);
	// OrbProjectileMesh->SetRelativeLocation(FVector(0, 8, 0));
	UGameplayStatics::SpawnEmitterAttached(ExplodeEffect, OrbProjectileMesh);
	GetWorldTimerManager().SetTimer(OrbDestroyTimer, this, &AEM_OrbProjectile::DestroyOrbProjectile, OrbDestroyDelay, true);
}

void AEM_OrbProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AActor* CurrentOwner = GetOwner();

	// TO DO: Make orb projectile explode only with enemy collision
	/*if (IsValid(OtherActor) && (OtherActor != CurrentOwner))
	{
		AEM_Character* OverlappedCharacter = Cast<AEM_Character>(OtherActor);

		if (IsValid(OverlappedCharacter))
		{
			ExplodeOrbProjectile();
		}
	}*/
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

void AEM_OrbProjectile::SetCharacterOwner(ACharacter* NewOwner)
{
	if (IsValid(NewOwner))
	{
		SetOwner(NewOwner);
		CurrentOwnerCharacter = NewOwner;
	}
}

