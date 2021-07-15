// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EM_Character.h"
#include "EM_Item.h"
#include "EM_Enemy.generated.h"

class AEM_PathActor;
class AEM_Item;
class AEM_AIController;
class AEM_FlameCurse;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Ultimate XP")
	float XPValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot System")
	float LootProbability;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Navigation Path")
	AEM_PathActor* MyPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot System")
	TSubclassOf<AEM_Item> LootItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Curses")
	TSubclassOf<AEM_FlameCurse> FlameCurseClass;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Controller")
	AEM_AIController* MyAIController;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void GiveXP(AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_GiveXP(AActor* DamageCauser);

	bool TrySpawnLoot();

	UFUNCTION()
	void HealthChange(UEM_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void CastFlames(FVector TargetLocation);

public:

	bool GetLoopPath() { return bLoopPath; };

	int GetDirectionIndex() { return DirectionIndex; };

	float GetWaitingTime() { return WaitingTimeOnPathPoint; };
};
