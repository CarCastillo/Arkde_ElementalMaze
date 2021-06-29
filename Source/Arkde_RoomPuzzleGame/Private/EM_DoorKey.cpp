// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_DoorKey.h"
#include "Components/StaticMeshComponent.h"
#include "EM_Character.h"

AEM_DoorKey::AEM_DoorKey()
{
	KeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	KeyMeshComponent->SetupAttachment(RootComponent);
	KeyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	XPValue = 100.0f;
	KeyTag = "KeyA";
}

void AEM_DoorKey::Pickup(AEM_Character* PickupCharacter)
{
	Super::Pickup(PickupCharacter);

	PickupCharacter->AddKey(KeyTag);
	PickupCharacter->GainUltimateXP(XPValue);
	Destroy();
}
