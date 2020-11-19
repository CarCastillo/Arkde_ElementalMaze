// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_GameMode.h"
#include "EM_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EM_SpectatingCamera.h"

void AEM_GameMode::BeginPlay()
{
	Super::BeginPlay();

	SetupSpectatingCameras();
}

void AEM_GameMode::SetupSpectatingCameras()
{
	TArray<AActor*> SpectatingCameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEM_SpectatingCamera::StaticClass(), SpectatingCameraActors);

	if (SpectatingCameraActors.Num() < 0)
	{
		for (AActor* SpectatingActor : SpectatingCameraActors)
		{
			AEM_SpectatingCamera* SpectatingCamera = Cast<AEM_SpectatingCamera>(SpectatingActor);

			if (IsValid(SpectatingCamera))
			{
				switch (SpectatingCamera->GetCameraType())
				{
				case EEM_SpectatingCameraType::CameraType_Victory:
					VictoryCamera = SpectatingCamera;
					break;

				case EEM_SpectatingCameraType::CameraType_GameOver:
					GameOverCamera = SpectatingCamera;
					break;

				default:
					break;
				}
			}
		}
	}
}

void AEM_GameMode::MoveCameraToSpectatingPoint(AEM_Character* Character, AEM_SpectatingCamera* SpectatingCamera)
{
	if (!IsValid(Character) || !IsValid(SpectatingCamera))
	{
		return;
	}

	AController* CharacterController = Character->GetController();

	if (IsValid(CharacterController))
	{
		APlayerController* PlayerController = Cast<APlayerController>(CharacterController);

		if (IsValid(PlayerController))
		{
			PlayerController->SetViewTargetWithBlend(SpectatingCamera, SpectatingBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}
}

void AEM_GameMode::Victory(AEM_Character* Character)
{
	Character->DisableInput(nullptr);

	MoveCameraToSpectatingPoint(Character, VictoryCamera);

	BP_Victory(Character);
}

void AEM_GameMode::GameOver(AEM_Character* Character)
{
	Character->GetMovementComponent()->StopMovementImmediately();
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (Character->HasToDestroy())
	{
		Character->DetachFromControllerPendingDestroy();
		Character->SetLifeSpan(5.0f);
	}
	else
	{
		Character->DisableInput(nullptr);
		MoveCameraToSpectatingPoint(Character, GameOverCamera);
	}

	BP_GameOver(Character);
}
