// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_LevelMusic.h"
#include "Components/AudioComponent.h"
#include "Components/BillboardComponent.h"
#include "EM_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EM_Character.h"

// Sets default values
AEM_LevelMusic::AEM_LevelMusic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MusicBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("MusicBillboardComponent"));
	RootComponent = MusicBillboardComponent;

	MusicAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent"));
	MusicAudioComponent->SetupAttachment(RootComponent);

	CriticalStatusParamName = "CriticalStatus";
}

// Called when the game starts or when spawned
void AEM_LevelMusic::BeginPlay()
{
	Super::BeginPlay();
	
	GameModeReference = Cast<AEM_GameMode>(GetWorld()->GetAuthGameMode());

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	PlayerCharacterReference = Cast<AEM_Character>(PlayerPawn);

	if (IsValid(GameModeReference))
	{
		GameModeReference->OnVictoryDelegate.AddDynamic(this, &AEM_LevelMusic::StopLevelMusic);
		GameModeReference->OnGameOverDelegate.AddDynamic(this, &AEM_LevelMusic::StopLevelMusic);
	}

	if (IsValid(PlayerCharacterReference))
	{
		PlayerCharacterReference->OnPlayerCriticalHealthStatusDelegate.AddDynamic(this, &AEM_LevelMusic::ChangeLevelMusic);
	}
}

void AEM_LevelMusic::StopLevelMusic()
{
	MusicAudioComponent->Stop();
}

void AEM_LevelMusic::ChangeLevelMusic(bool bIsPlayerInCriticalStatus)
{
	if (bIsPlayerInCriticalStatus)
	{
		MusicAudioComponent->SetBoolParameter(CriticalStatusParamName, bIsPlayerInCriticalStatus);
	}
}
