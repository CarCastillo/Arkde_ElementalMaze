// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_Item.h"
#include "Components/SphereComponent.h"
#include "EM_Character.h"

// Sets default values
AEM_Item::AEM_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	RootComponent = MainColliderComponent;
}

// Called when the game starts or when spawned
void AEM_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEM_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEM_Item::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor))
	{
		AEM_Character* OverlappedCharacter = Cast<AEM_Character>(OtherActor);

		if (IsValid(OverlappedCharacter) && OverlappedCharacter->GetCharacterType() == EEM_CharacterType::CharacterType_Player)
		{
			Pickup(OverlappedCharacter);
		}
	}
}

void AEM_Item::Pickup(AEM_Character* PickupCharacter)
{
	BP_Pickup(PickupCharacter);
}
