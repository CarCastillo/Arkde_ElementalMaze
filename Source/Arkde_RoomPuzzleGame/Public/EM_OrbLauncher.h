// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EM_Weapon.h"
#include "EM_OrbLauncher.generated.h"

class AEM_OrbProjectile;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_OrbLauncher : public AEM_Weapon
{
	GENERATED_BODY()

public:

	AEM_OrbLauncher();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Orb Launcher")
	TSubclassOf<AEM_OrbProjectile> OrbProjectileClass;

protected:

	virtual void StartAction() override;

	virtual void StopAction() override;	
};
