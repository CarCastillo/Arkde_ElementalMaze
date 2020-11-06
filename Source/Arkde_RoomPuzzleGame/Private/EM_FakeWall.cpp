// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_FakeWall.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEM_FakeWall::AEM_FakeWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FakeWallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FakeWallMeshComponent"));
	RootComponent = FakeWallMeshComponent;

	FakeWallColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("FakeWallColliderComponent"));
	FakeWallColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FakeWallColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	FakeWallColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	FakeWallColliderComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEM_FakeWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEM_FakeWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

