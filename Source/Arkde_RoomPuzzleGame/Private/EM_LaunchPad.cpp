// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_LaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "EM_Character.h"

AEM_LaunchPad::AEM_LaunchPad()
{
	LaunchAngle = 55.0f;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = CustomRootComponent;

	LaunchPadColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchPadColliderComponent"));
	MainColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	LaunchPadColliderComponent->SetupAttachment(RootComponent);

	LaunchPadMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchPadMeshComponent"));
	LaunchPadMeshComponent->SetupAttachment(RootComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->SetupAttachment(RootComponent);
}

// Called every frame
void AEM_LaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEM_LaunchPad::Pickup(AEM_Character* CharacterToLaunch)
{
	Super::Pickup(CharacterToLaunch);

	TextRenderComponent->SetVisibility(true);
	CharacterToLaunch->CurrentLaunchPad = this;
}

void AEM_LaunchPad::LaunchPlayer(AEM_Character* CharacterToLaunch)
{
	FRotator LaunchRotation = GetActorRotation();
	LaunchRotation.Pitch += LaunchAngle;
	CharacterToLaunch->LaunchCharacter(LaunchRotation.Vector() * 1100.0f, false, false);

	FRotator LaunchPadRotation = FRotator(-35.0f, 0.0f, 0.0f);
	CustomRootComponent->SetRelativeRotation(LaunchPadRotation);
}

void AEM_LaunchPad::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (IsValid(OtherActor))
	{
		AEM_Character* OverlappedCharacter = Cast<AEM_Character>(OtherActor);

		if (IsValid(OverlappedCharacter))
		{
			OverlappedCharacter->CurrentLaunchPad = nullptr;

			TextRenderComponent->SetVisibility(false);
			/* TO DO: Set rotation to zero after overlapping ends */
			/* FRotator LaunchPadRotation = FRotator(0.0f, 0.0f, 0.0f);
			CustomRootComponent->SetRelativeRotation(LaunchPadRotation); */
		}
	}
}

