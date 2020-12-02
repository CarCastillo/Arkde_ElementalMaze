// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EM_GameMode.generated.h"

class AEM_Character;
class AEM_SpectatingCamera;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spectating Camera")
	float SpectatingBlendTimeDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spectating Camera")
	float BlendTimeDelay;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
	AEM_SpectatingCamera* VictoryCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
	AEM_SpectatingCamera* GameOverCamera;

	FTimerDelegate CameraBlendTimerDel;

	FTimerHandle CameraBlendTimer;

protected:

	virtual void BeginPlay() override;

	void SetupSpectatingCameras();

	void MoveCameraToSpectatingPoint(AEM_Character* Character, AEM_SpectatingCamera* SpectatingCamera);
 
public:

	AEM_GameMode();
	
	UFUNCTION()
	void Victory(AEM_Character* Character);
	
	UFUNCTION()
	void GameOver(AEM_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Victory(AEM_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GameOver(AEM_Character* Character);
};
