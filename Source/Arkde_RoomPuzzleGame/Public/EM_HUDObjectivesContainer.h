// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EM_HUDObjectivesContainer.generated.h"

class AEM_GameMode;
class UEM_HUDObjective;

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API UEM_HUDObjectivesContainer : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	AEM_GameMode* GameModeReference;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	TArray<UEM_HUDObjective*> Objectives;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION(BlueprintCallable)
	void InitializeObjectives(TArray<UEM_HUDObjective*> NewObjectives);

	UFUNCTION()
	void UpdateItemObjectives(int RequiredItems);

};
