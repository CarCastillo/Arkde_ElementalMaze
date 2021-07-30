// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_HUDGameState.h"
#include "EM_GameMode.h"

void UEM_HUDGameState::InitializeWidget()
{
	GameModeReference = Cast<AEM_GameMode>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameModeReference))
	{
		GameModeReference->OnVictoryDelegate.AddDynamic(this, &UEM_HUDGameState::OnVictory);
		GameModeReference->OnGameOverDelegate.AddDynamic(this, &UEM_HUDGameState::OnGameOver);
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UEM_HUDGameState::OnVictory()
{
	GameStateName = VictoryMessage;
	SetVisibility(ESlateVisibility::Visible);
}

void UEM_HUDGameState::OnGameOver()
{
	GameStateName = GameOverMessage;
	SetVisibility(ESlateVisibility::Visible);
}
