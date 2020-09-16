// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_LaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EM_Character.h"

AEM_LaunchPad::AEM_LaunchPad()
{
	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = CustomRootComponent;

	LaunchPadColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchPadColliderComponent"));
	MainColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	LaunchPadColliderComponent->SetupAttachment(RootComponent);

	LaunchPadMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchPadMeshComponent"));
	LaunchPadMeshComponent->SetupAttachment(RootComponent);
}

// Called every frame
void AEM_LaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//LaunchPlayer();
}

void AEM_LaunchPad::Pickup(AEM_Character* CharacterToLaunch)
{
	Super::Pickup(CharacterToLaunch);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Press Enter, Circle or B to activate the launch pad."));

	if (CharacterToLaunch->bIsLaunchPadActivated)
	{
		FRotator LaunchRotation = GetActorRotation();
		LaunchRotation.Pitch += 90.0f;
		CharacterToLaunch->LaunchCharacter(LaunchRotation.Vector() * 850.0f, false, false);

		FRotator LaunchPadRotation = FRotator(-35.0f, 0.0f, 0.0f);
		CustomRootComponent->SetRelativeRotation(LaunchPadRotation);
		CharacterToLaunch->bIsLaunchPadActivated = false;
	}
}

