// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_GameMode.h"
#include "EM_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EM_SpectatingCamera.h"
#include "Sound/SoundCue.h"
#include "EM_Enemy.h"

AEM_GameMode::AEM_GameMode()
{
	MainMenuMapName = "MainMenuMap";
	BlendTimeDelay = 2.0f;
}

void AEM_GameMode::AddKeyToCharacter(AEM_Character* KeyOwner, FName KeyTag)
{
	if (IsValid(KeyOwner))
	{
		KeyOwner->AddKey(KeyTag);
		int CollectedKeys = KeyOwner->GetMazeKeys();

		if (CollectedKeys == 3)
		{
			bTotalEnergyCollected = true;
			OnKeyAddedDelegate.Broadcast(CollectedKeys);
			NotifyObjectivesCompletedStatus();
		}
	}
}

void AEM_GameMode::VerifyEnemiesDefeated(AActor* Enemy)
{
	EnemiesDefeated.AddUnique(Enemy);

	if (EnemiesDefeated.Num() == GetEnemiesCount())
	{
		OnEnemiesDefeatedDelegate.Broadcast();
		NotifyObjectivesCompletedStatus();
	}
}

void AEM_GameMode::NotifyObjectivesCompletedStatus()
{
	if (bTotalEnergyCollected && EnemiesDefeated.Num() == GetEnemiesCount())
	{
		OnGameObjectivesCompletedDelegate.Broadcast();
	}
}

void AEM_GameMode::BeginPlay()
{
	Super::BeginPlay();

	SetupSpectatingCameras();
	GetEnemiesCount();
}

void AEM_GameMode::SetupSpectatingCameras()
{
	TArray<AActor*> SpectatingCameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEM_SpectatingCamera::StaticClass(), SpectatingCameraActors);

	if (SpectatingCameraActors.Num() > 0)
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

int AEM_GameMode::GetEnemiesCount()
{
	TArray<AActor*> EnemiesList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEM_Enemy::StaticClass(), EnemiesList);

	return EnemiesList.Num();
}

void AEM_GameMode::MoveCameraToSpectatingPoint(AEM_Character* Character, AEM_SpectatingCamera* SpectatingCamera)
{
	UE_LOG(LogTemp, Warning, TEXT("Enter to MoveCameraToSpectatingPoint function"));
	if (!IsValid(Character) || !IsValid(SpectatingCamera))
	{
		UE_LOG(LogTemp, Warning, TEXT("Not valid Character or SpectatingCamera"));
		return;
	}

	AController* CharacterController = Character->GetController();

	if (IsValid(CharacterController))
	{
		APlayerController* PlayerController = Cast<APlayerController>(CharacterController);

		if (IsValid(PlayerController))
		{
			PlayerController->SetViewTargetWithBlend(SpectatingCamera, SpectatingBlendTimeDuration, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}
}

void AEM_GameMode::PlayMusic(USoundCue* MusicCue)
{
	if (!IsValid(MusicCue))
	{
		return;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), MusicCue);
}

void AEM_GameMode::Victory(AEM_Character* Character)
{
	Character->DisableInput(nullptr);

	MoveCameraToSpectatingPoint(Character, VictoryCamera);
	OnVictoryDelegate.Broadcast();
	PlayMusic(VictoryMusic);

	GetWorld()->GetTimerManager().SetTimer(BackToMainMenuTimer, this, &AEM_GameMode::BackToMainMenu, 10.0f, false);

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
		CameraBlendTimerDel = FTimerDelegate::CreateUObject(this, &AEM_GameMode::MoveCameraToSpectatingPoint, Character, GameOverCamera);
		GetWorldTimerManager().SetTimer(CameraBlendTimer, CameraBlendTimerDel, BlendTimeDelay, true);
	}

	OnGameOverDelegate.Broadcast();
	PlayMusic(GameOverMusic);

	GetWorld()->GetTimerManager().SetTimer(BackToMainMenuTimer, this, &AEM_GameMode::BackToMainMenu, 15.0f, false);

	BP_GameOver(Character);
}

void AEM_GameMode::BackToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), MainMenuMapName);
}
