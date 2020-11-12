// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_GameMode.h"
#include "EM_Character.h"

void AEM_GameMode::Victory(AEM_Character* Character)
{
	Character->DisableInput(nullptr);
	BP_Victory(Character);
}

void AEM_GameMode::GameOver()
{
	BP_GameOver();
}
