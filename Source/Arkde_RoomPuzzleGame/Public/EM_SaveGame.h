// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "EM_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API UEM_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "Data")
	int EnemiesDefeatedCounter;

public:

	UFUNCTION(BlueprintCallable)
	int GetEnemiesDefeatedCounterInfo() { return EnemiesDefeatedCounter; };

	UFUNCTION(BlueprintCallable)
	void SetEnemiesDefeatedCounterInfo(int NewValue) { EnemiesDefeatedCounter = NewValue; };
};
