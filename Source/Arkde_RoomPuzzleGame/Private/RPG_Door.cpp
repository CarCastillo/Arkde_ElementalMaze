// Fill out your copyright notice in the Description page of Project Settings.


#include "RPG_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "EM_Character.h"

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

	KeyZoneColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyZoneCollider"));
	KeyZoneColliderComponent->SetupAttachment(CustomRootComponent);
	KeyZoneColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	KeyZoneColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	KeyZoneColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	openAngle = -90.0f;
	DoorTag = "KeyA";
}

// Called when the game starts or when spawned
void ARPG_Door::BeginPlay()
{
	Super::BeginPlay();
	KeyZoneColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ARPG_Door::CheckKeyFromPlayer);
}

void ARPG_Door::CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsOpen)
	{
		return;
	}

	if (IsValid(OtherActor))
	{
		AEM_Character* OverlappedCharacter = Cast<AEM_Character>(OtherActor);

		if (IsValid(OverlappedCharacter))
		{
			if (OverlappedCharacter->HasKey(DoorTag))
			{
				OpenDoor();
			}
		}
	}
}

// Called every frame
void ARPG_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARPG_Door::OpenDoor()
{
	/* FRotator newRotation = FRotator(0.0f, openAngle, 0.0f);
	DoorComponent->SetRelativeRotation(newRotation); */
	
	bIsOpen = true;
	BP_OpenDoor();
}
