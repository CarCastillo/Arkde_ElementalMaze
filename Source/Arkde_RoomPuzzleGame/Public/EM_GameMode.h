// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EM_GameMode.generated.h"

class AEM_Character;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void Victory(AEM_Character* Character);
	
	UFUNCTION()
	void GameOver();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Victory(AEM_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GameOver();
};
