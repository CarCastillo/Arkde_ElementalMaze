// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_EnemyHealthBar.h"

void UEM_EnemyHealthBar::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	HealthPercent = CurrentHealth / MaxHealth;
}
