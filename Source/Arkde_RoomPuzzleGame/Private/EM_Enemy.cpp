// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_Enemy.h"
#include "EM_HealthComponent.h"
#include "EM_Character.h"
#include "EM_Weapon.h"
#include "Components/CapsuleComponent.h"
#include "EM_Item.h"

AEM_Enemy::AEM_Enemy() 
{
	bLoopPath = false;
	DirectionIndex = 1;
	WaitingTimeOnPathPoint = 1.0f;
	XPValue = 20.0f;
	LootProbability = 100.0f;
}

void AEM_Enemy::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeadDelegate.AddDynamic(this, &AEM_Enemy::GiveXP);
}

void AEM_Enemy::TakingDamage(UEM_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (HealthComponent->IsDead())
	{
		Destroy();
	}
}

void AEM_Enemy::GiveXP(AActor* DamageCauser)
{
	AEM_Character* PossiblePlayer = Cast<AEM_Character>(DamageCauser);

	if (IsValid(PossiblePlayer) && PossiblePlayer->GetCharacterType() == EEM_CharacterType::CharacterType_Player)
	{
		PossiblePlayer->GainUltimateXP(XPValue);
		TrySpawnLoot();
	}

	AEM_Weapon* PossibleWeapon = Cast<AEM_Weapon>(DamageCauser);

	if (IsValid(PossibleWeapon))
	{
		AEM_Character* WeaponOwner = Cast<AEM_Character>(PossibleWeapon->GetOwner());

		if (IsValid(WeaponOwner) && WeaponOwner->GetCharacterType() == EEM_CharacterType::CharacterType_Player)
		{
			WeaponOwner->GainUltimateXP(XPValue);
			TrySpawnLoot();
		}
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StopWeaponAction();

	BP_GiveXP(DamageCauser);
}

bool AEM_Enemy::TrySpawnLoot()
{
	if (!IsValid(LootItemClass))
	{
		return false;
	}

	float SelectedProbability = FMath::RandRange(0.0f, 100.0f);

	if (SelectedProbability <= LootProbability)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AEM_Item>(LootItemClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);
	}

	return true;
}
