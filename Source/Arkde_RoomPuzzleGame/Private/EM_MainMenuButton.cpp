// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_MainMenuButton.h"

UEM_MainMenuButton::UEM_MainMenuButton()
{
	CheckFocusRate = 0.1f;
}

void UEM_MainMenuButton::Start()
{
	GetWorld()->GetTimerManager().SetTimer(CheckFocusTimer, this, &UEM_MainMenuButton::CheckFocus, CheckFocusRate, true);
}

void UEM_MainMenuButton::CheckFocus()
{
	if (IsHovered())
	{
		SetKeyboardFocus();
		SetButtonStyle(EEM_ButtonStyleType::ButtonStyleType_Mouse);
	}
	else
	{
		EEM_ButtonStyleType StyleTypeSelected = HasKeyboardFocus() ? EEM_ButtonStyleType::ButtonStyleType_KeySelected : EEM_ButtonStyleType::ButtonStyleType_KeyNotSelected;
		SetButtonStyle(StyleTypeSelected);
	}
}

void UEM_MainMenuButton::SetButtonStyle(EEM_ButtonStyleType NewStyleType)
{
	BP_SetButtonStyle(NewStyleType);
}
