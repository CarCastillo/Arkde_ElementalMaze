// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_LifeOrb.h"
#include "Components/StaticMeshComponent.h"
#include "EM_Character.h"

AEM_LifeOrb::AEM_LifeOrb()
{
	LifeOrbMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LifeOrbMeshComponent"));
	LifeOrbMeshComponent->SetupAttachment(RootComponent);
	LifeOrbMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthValue = 15.0f;
}

void AEM_LifeOrb::Pickup(AEM_Character* PickupCharacter)
{
	Super::Pickup(PickupCharacter);

	if (PickupCharacter->GetCharacterType() == EEM_CharacterType::CharacterType_Player)
	{
		PickupCharacter->HealCharacter(HealthValue);

		Destroy();
	}
	
}
