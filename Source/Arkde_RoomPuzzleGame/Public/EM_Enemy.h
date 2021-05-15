// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EM_Character.h"
#include "EM_Enemy.generated.h"

class AEM_PathActor;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_Enemy : public AEM_Character
{
	GENERATED_BODY()

public:

	AEM_Enemy();
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "AI|Navigation Path")
	bool bLoopPath;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "AI|Navigation Path")
	int DirectionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "AI|Navigation Path")
	float WaitingTimeOnPathPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Navigation Path")
	AEM_PathActor* MyPath;

protected:

	UFUNCTION()
	void TakingDamage(UEM_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

};
