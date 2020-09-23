// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_OrbProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AEM_OrbProjectile::AEM_OrbProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	
}

// Called every frame
void AEM_OrbProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

