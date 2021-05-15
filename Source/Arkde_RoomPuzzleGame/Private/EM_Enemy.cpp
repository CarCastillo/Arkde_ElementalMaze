// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_Enemy.h"
#include "EM_HealthComponent.h"

AEM_Enemy::AEM_Enemy() 
{
	bLoopPath = false;
	DirectionIndex = 1;
	WaitingTimeOnPathPoint = 1.0f;
}

void AEM_Enemy::TakingDamage(UEM_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (HealthComponent->IsDead())
	{
		Destroy();
	}
}
