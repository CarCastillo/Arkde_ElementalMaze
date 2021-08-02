// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EM_LevelMusic.generated.h"

class UAudioComponent;
class UBillboardComponent;
class AEM_GameMode;
class AEM_Character;

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_LevelMusic : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBillboardComponent* MusicBillboardComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAudioComponent* MusicAudioComponent;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music")
	FName CriticalStatusParamName;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	AEM_GameMode* GameModeReference;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	AEM_Character* PlayerCharacterReference;

public:	
	// Sets default values for this actor's properties
	AEM_LevelMusic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void StopLevelMusic();

	UFUNCTION()
	void ChangeLevelMusic(bool bIsPlayerInCriticalStatus);
};
