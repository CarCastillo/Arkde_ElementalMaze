// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_Dummy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEM_Dummy::AEM_Dummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	bIsDummyOnMovement = true;
	PrimaryActorTick.bCanEverTick = bIsDummyOnMovement;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = CustomRootComponent;

	DummyMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DummyMeshComponent"));
	DummyMeshComponent->SetupAttachment(CustomRootComponent);

	CapsuleColliderComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleColliderComponent"));
	CapsuleColliderComponent->SetupAttachment(CustomRootComponent);

	bIsGoingRight = true;
	dummySpeed = 1.0f;
	leftMovementDistance = -1200.0f;
	rightMovementDistance = -500.0f;
}

// Called when the game starts or when spawned
void AEM_Dummy::BeginPlay()
{
	Super::BeginPlay();
}

void AEM_Dummy::Move()
{
	FVector rightDirection = UKismetMathLibrary::GetForwardVector(GetActorRotation());

	if (bIsGoingRight)
	{
		rightDirection = rightDirection;
	}
	else
	{
		rightDirection = rightDirection * -1;
	}

	FVector currentVelocity = rightDirection * dummySpeed;
	FVector newPosition = GetActorLocation() + currentVelocity;
	SetActorLocation(newPosition);

	if ((bIsGoingRight && GetActorLocation().X >= rightMovementDistance) || (!bIsGoingRight && GetActorLocation().X <= leftMovementDistance))
	{
		bIsGoingRight = !bIsGoingRight;
	}
}

// Called every frame
void AEM_Dummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDummyOnMovement)
	{
		Move();
	}	
}

