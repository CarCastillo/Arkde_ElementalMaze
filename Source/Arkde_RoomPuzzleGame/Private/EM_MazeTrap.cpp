// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_MazeTrap.h"
#include "EM_Character.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEM_MazeTrap::AEM_MazeTrap()
{
	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = CustomRootComponent;
}

// Called when the game starts or when spawned
void AEM_MazeTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEM_MazeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEM_MazeTrap::Explode()
{
	UE_LOG(LogTemp, Warning, TEXT("EXPLODEE MINE!!!"));
	DrawDebugSphere(GetWorld(), CustomRootComponent->GetComponentLocation(), 150.0f, 32, FColor::Red, false, 2.0f);
	UGameplayStatics::SpawnEmitterAttached(ExplodeEffect, CustomRootComponent);
}

void AEM_MazeTrap::DestroyTrap()
{
}

