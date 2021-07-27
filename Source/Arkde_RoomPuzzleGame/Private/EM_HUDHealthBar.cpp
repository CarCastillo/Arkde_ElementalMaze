// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_HUDHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "EM_Character.h"
#include "EM_HealthComponent.h"

void UEM_HUDHealthBar::InitializeWidget()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (IsValid(PlayerPawn))
	{
		AEM_Character* PlayerCharacter = Cast<AEM_Character>(PlayerPawn);

		if (IsValid(PlayerCharacter))
		{
			UEM_HealthComponent* PlayerHealthComponent = PlayerCharacter->GetHealthComponent();

			if (IsValid(PlayerHealthComponent))
			{
				PlayerHealthComponent->OnHealthUpdateDelegate.AddDynamic(this, &UEM_HUDHealthBar::UpdateHealth);
			}
		}
	}
}

void UEM_HUDHealthBar::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	HealthPercent = CurrentHealth / MaxHealth;
	HealthColor = FMath::Lerp(EmptyHealthColor, FullHealthColor, HealthPercent);
}
