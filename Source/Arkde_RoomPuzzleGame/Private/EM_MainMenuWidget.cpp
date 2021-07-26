// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"
#include "EM_GameInstance.h"

void UEM_MainMenuWidget::NewGame()
{
	BP_NewGame();

	UEM_GameInstance* GameInstanceReference = Cast<UEM_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->ResetData();
	}

	UGameplayStatics::OpenLevel(GetWorld(), GameplayLevelName);
}

void UEM_MainMenuWidget::ContinueGame()
{
	BP_ContinueGame();

	UEM_GameInstance* GameInstanceReference = Cast<UEM_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->LoadData();
	}

	UGameplayStatics::OpenLevel(GetWorld(), GameplayLevelName);
}

void UEM_MainMenuWidget::QuitGame()
{
	BP_QuitGame();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
}
