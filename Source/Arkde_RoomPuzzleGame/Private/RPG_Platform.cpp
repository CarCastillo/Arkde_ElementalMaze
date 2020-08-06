// Fill out your copyright notice in the Description page of Project Settings.


#include "RPG_Platform.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARPG_Platform::ARPG_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = CustomRootComponent;

	PlatformMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaformMesh"));
	PlatformMeshComponent->SetupAttachment(CustomRootComponent);

	bIsGoingUp = true;
	speed = 10;
	minHeight = 0.0f;
	maxHeight = 50.0f;
}

// Called when the game starts or when spawned
void ARPG_Platform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPG_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ARPG_Platform::Move()
{
	FVector upDirection = UKismetMathLibrary::GetUpVector(GetActorRotation());

	if (bIsGoingUp)
	{
		upDirection = upDirection;
	} 
	else
	{
		upDirection = upDirection * -1;
	}

	FVector currentVelocity = upDirection * speed;
	FVector newPosition = GetActorLocation() + currentVelocity;
	SetActorLocation(newPosition);

	if ((bIsGoingUp && GetActorLocation().Z >= maxHeight) || (!bIsGoingUp && GetActorLocation().Z <= minHeight))
	{
		bIsGoingUp = !bIsGoingUp;
	}
}

