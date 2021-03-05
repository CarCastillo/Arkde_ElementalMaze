// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_VictoryZone.h"
#include "Components/BoxComponent.h"
#include "EM_Character.h"
#include "EM_GameMode.h"

// Sets default values
AEM_VictoryZone::AEM_VictoryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VictoryZoneComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("VictoryZoneComponent"));
	RootComponent = VictoryZoneComponent;
	VictoryZoneComponent->SetBoxExtent(FVector(100.0f));
}

// Called when the game starts or when spawned
void AEM_VictoryZone::BeginPlay()
{
	Super::BeginPlay();
	
	GameModeReference = Cast<AEM_GameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AEM_VictoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEM_VictoryZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (IsValid(OtherActor) && IsValid(GameModeReference))
	{
		AEM_Character* EMCharacter = Cast<AEM_Character>(OtherActor);

		if (IsValid(EMCharacter) && EMCharacter->GetCharacterType() == EEM_CharacterType::CharacterType_Player)
		{
			GameModeReference->Victory(EMCharacter);
		}
	}
}

