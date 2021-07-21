// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "EM_MainMenuButton.generated.h"

UENUM(Blueprintable)
enum class EEM_ButtonStyleType : uint8
{
	ButtonStyleType_Mouse			UMETA(DisplayName = "Selected by mouse"),
	ButtonStyleType_KeySelected		UMETA(DisplayName = "Selected by keyboard"),
	ButtonStyleType_KeyNotSelected	UMETA(DisplayName = "Not Selected by keyboard")
};

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API UEM_MainMenuButton : public UButton
{
	GENERATED_BODY()

public:

	UEM_MainMenuButton();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MainMenuButton")
	float CheckFocusRate;

	FTimerHandle CheckFocusTimer;

protected:

	UFUNCTION(BlueprintCallable, Category = "MainMenuButton")
	void Start();

	void CheckFocus();

	void SetButtonStyle(EEM_ButtonStyleType NewStyleType);

	UFUNCTION(BlueprintImplementableEvent, Category = "MainMenuButton")
	void BP_SetButtonStyle(EEM_ButtonStyleType NewStyleType);
	
};
