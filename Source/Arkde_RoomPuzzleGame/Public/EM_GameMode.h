// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EM_GameMode.generated.h"

class AEM_Character;
class AEM_SpectatingCamera;
class USoundCue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKeyAddedSignature, int, CollectedKeys);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemiesDefeatedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStateChangeSignature);

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spectating Camera")
	float SpectatingBlendTimeDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spectating Camera")
	float BlendTimeDelay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Flow")
	FName MainMenuMapName;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
	AEM_SpectatingCamera* VictoryCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
	AEM_SpectatingCamera* GameOverCamera;

	FTimerDelegate CameraBlendTimerDel;

	FTimerHandle CameraBlendTimer;

	FTimerHandle BackToMainMenuTimer;

	TArray<FName> MazeKeys;

	TArray<AActor*> EnemiesDefeated;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundCue* VictoryMusic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundCue* GameOverMusic;

public:

	UPROPERTY(BlueprintAssignable)
	FOnKeyAddedSignature OnKeyAddedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnEnemiesDefeatedSignature OnEnemiesDefeatedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnGameStateChangeSignature OnVictoryDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnGameStateChangeSignature OnGameOverDelegate;

protected:

	virtual void BeginPlay() override;

	void SetupSpectatingCameras();

	int GetEnemiesCount();

	void MoveCameraToSpectatingPoint(AEM_Character* Character, AEM_SpectatingCamera* SpectatingCamera);

	void PlayMusic(USoundCue* MusicCue);
 
public:

	AEM_GameMode();
	
	UFUNCTION()
	void AddKeyToCharacter(AEM_Character* KeyOwner, FName KeyTag);

	UFUNCTION()
	void VerifyEnemiesDefeated(AActor* Enemy);

	UFUNCTION()
	void Victory(AEM_Character* Character);
	
	UFUNCTION()
	void GameOver(AEM_Character* Character);

	void BackToMainMenu();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Victory(AEM_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GameOver(AEM_Character* Character);
};
