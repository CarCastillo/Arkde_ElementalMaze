// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EM_HUDGameState.generated.h"

class AEM_GameMode;

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API UEM_HUDGameState : public UUserWidget
{
	GENERATED_BODY()
	
protected: 

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FName GameStateName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FName VictoryMessage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FName GameOverMessage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FName ObjectivesCompletedMessage;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	AEM_GameMode* GameModeReference;

	FTimerHandle HideMessageTimer;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION()
	void OnVictory();

	UFUNCTION()
	void OnGameOver();

	UFUNCTION()
	void OnObjectivesCompleted();

	void HideMessage();

};
