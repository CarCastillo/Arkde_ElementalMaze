// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_HUDObjectivesContainer.h"
#include "EM_GameMode.h"
#include "EM_HUDObjective.h"

void UEM_HUDObjectivesContainer::InitializeWidget()
{
	GameModeReference = Cast<AEM_GameMode>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameModeReference))
	{
		GameModeReference->OnKeyAddedDelegate.AddDynamic(this, &UEM_HUDObjectivesContainer::UpdateItemObjectives);
	}
}

void UEM_HUDObjectivesContainer::InitializeObjectives(TArray<UEM_HUDObjective*> NewObjectives)
{
	for (UEM_HUDObjective* NewObjective : NewObjectives)
	{
		Objectives.AddUnique(NewObjective);
	}
}

void UEM_HUDObjectivesContainer::UpdateItemObjectives(int RequiredItems)
{
	int ObjectiveIndex = -1;

	if (RequiredItems == 3)
	{
		ObjectiveIndex = 0;
		
		if (Objectives.IsValidIndex(ObjectiveIndex))
		{
			UEM_HUDObjective* CurrentObjective = Objectives[ObjectiveIndex];

			if (IsValid(CurrentObjective))
			{
				CurrentObjective->ObjectiveCompleted();
			}
		}
	}
}
