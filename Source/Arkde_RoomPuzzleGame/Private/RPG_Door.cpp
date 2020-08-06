// Fill out your copyright notice in the Description page of Project Settings.


#include "RPG_Door.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARPG_Door::ARPG_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = CustomRootComponent;

	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrameComponent->SetupAttachment(CustomRootComponent);

	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorComponent->SetupAttachment(CustomRootComponent);

	openAngle = -90.0f;

}

// Called when the game starts or when spawned
void ARPG_Door::BeginPlay()
{
	Super::BeginPlay();

	OpenDoor();
	
}

// Called every frame
void ARPG_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARPG_Door::OpenDoor()
{
	FRotator newRotation = FRotator(0.0f, openAngle, 0.0f);
	DoorComponent->SetRelativeRotation(newRotation);
}
