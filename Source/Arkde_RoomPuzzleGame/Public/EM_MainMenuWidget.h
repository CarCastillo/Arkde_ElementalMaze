// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EM_MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API UEM_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MainMenu")
	FName GameplayLevelName;

protected:

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void NewGame();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void ContinueGame();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void QuitGame();

	UFUNCTION(BlueprintImplementableEvent, Category = "MainMenu")
	void BP_NewGame();

	UFUNCTION(BlueprintImplementableEvent, Category = "MainMenu")
	void BP_ContinueGame();

	UFUNCTION(BlueprintImplementableEvent, Category = "MainMenu")
	void BP_QuitGame();
	
};
