// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "EM_SaveGame.h"

UEM_GameInstance::UEM_GameInstance()
{
	SaveSlotName = "EM_SaveData";
}

void UEM_GameInstance::AddEnemyDefeatedToCounter()
{
	EnemiesDefeatedCounter++;
	BP_AddEnemyDefeatedToCounter();
}

void UEM_GameInstance::SaveData()
{
	USaveGame* SaveGameObject = nullptr;
	bool bExistingData = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);

	if (bExistingData)
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	}
	else
	{
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(UEM_SaveGame::StaticClass());
	}

	if (IsValid(SaveGameObject))
	{
		UEM_SaveGame* SaveFile = Cast<UEM_SaveGame>(SaveGameObject);

		if (IsValid(SaveFile))
		{
			SaveFile->SetEnemiesDefeatedCounterInfo(EnemiesDefeatedCounter);

			UGameplayStatics::SaveGameToSlot(SaveFile, SaveSlotName, 0);
		}
	}
}

void UEM_GameInstance::LoadData()
{
	USaveGame* SaveGameObject = nullptr;
	bool bExistingData = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);

	if (bExistingData)
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	}

	if (IsValid(SaveGameObject))
	{
		UEM_SaveGame* SaveFile = Cast<UEM_SaveGame>(SaveGameObject);

		if (IsValid(SaveFile))
		{
			EnemiesDefeatedCounter = SaveFile->GetEnemiesDefeatedCounterInfo();
		}
	}
}

void UEM_GameInstance::ResetData()
{
	EnemiesDefeatedCounter = 0;
	BP_ResetData();
}
