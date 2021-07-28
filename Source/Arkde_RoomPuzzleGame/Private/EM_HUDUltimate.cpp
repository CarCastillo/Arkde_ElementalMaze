// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_HUDUltimate.h"
#include "Kismet/GameplayStatics.h"
#include "EM_Character.h"

void UEM_HUDUltimate::InitializeWidget()
{
	UltimateColor = UltimateDisabledColor;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (IsValid(PlayerPawn))
	{
		AEM_Character* PlayerCharacter = Cast<AEM_Character>(PlayerPawn);

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->OnUltimateUpdateDelegate.AddDynamic(this, &UEM_HUDUltimate::UpdateUltimateValue);
			PlayerCharacter->OnUltimateStatusDelegate.AddDynamic(this, &UEM_HUDUltimate::UpdateUltimateStatus);
		}
	}
}

void UEM_HUDUltimate::UpdateUltimateValue(float CurrentUltimateXP, float MaxUltimateXP)
{
	UltimatePercent = CurrentUltimateXP / MaxUltimateXP;
}

void UEM_HUDUltimate::UpdateUltimateStatus(bool bIsAvailable)
{
	UltimateColor = bIsAvailable ? UltimateEnabledColor : UltimateDisabledColor;
}
