// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_DoorKey.h"
#include "Components/StaticMeshComponent.h"
#include "EM_Character.h"
#include "EM_GameMode.h"

AEM_DoorKey::AEM_DoorKey()
{
	KeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	KeyMeshComponent->SetupAttachment(RootComponent);
	KeyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	KeyTag = "KeyA";
}

void AEM_DoorKey::Pickup(AEM_Character* PickupCharacter)
{
	Super::Pickup(PickupCharacter);

	if (IsValid(PickupCharacter) && PickupCharacter->GetCharacterType() == EEM_CharacterType::CharacterType_Player)
	{
		if (IsValid(GameModeReference))
		{
			GameModeReference->AddKeyToCharacter(PickupCharacter, KeyTag);
		}

		Destroy();
	}
}
