// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_HUDObjective.h"

void UEM_HUDObjective::ObjectiveCompleted()
{
	bIsCompleted = true;
	CurrentColor = CompletedColor;
}
