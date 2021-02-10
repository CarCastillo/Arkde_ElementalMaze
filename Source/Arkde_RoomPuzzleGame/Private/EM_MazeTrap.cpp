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

void AEM_MazeTrap::Explode(float DestroyTime)
{
	UGameplayStatics::SpawnEmitterAttached(ExplodeEffect, CustomRootComponent);
	GetWorldTimerManager().SetTimer(TrapDestroyTimer, this, &AEM_MazeTrap::DestroyTrap, DestroyTime, true);
}

void AEM_MazeTrap::DestroyTrap()
{
	Destroy();
}

