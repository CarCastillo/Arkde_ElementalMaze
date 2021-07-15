// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_ElementalCurse.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEM_ElementalCurse::AEM_ElementalCurse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = CustomRootComponent;
}

// Called when the game starts or when spawned
void AEM_ElementalCurse::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::SpawnEmitterAttached(ElementalCurseEffect, CustomRootComponent);
	SetLifeSpan(5.0f);
}

// Called every frame
void AEM_ElementalCurse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

