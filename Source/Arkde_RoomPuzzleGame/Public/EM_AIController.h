// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EM_AIController.generated.h"

class UBehaviorTree;
class AEM_Enemy;
class UBlackboardComponent;
class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_AIController : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAIPerceptionComponent* AIPerceptionComponent;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "EnemyController")
	bool bReceivingDamage;

	UPROPERTY(BlueprintReadOnly, Category = "EnemyController")
	AEM_Enemy* MyEnemy;

	UPROPERTY(BlueprintReadOnly, Category = "EnemyController")
	UBlackboardComponent* MyBlackboard;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyController")
	UBehaviorTree* EnemyBehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyController")
	FName LoopPathParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyController")
	FName DirectionIndexParemeterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyController")
	FName WaitingTimeParemeterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyController")
	FName CanSeePlayerParemeterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyController")
	FName InvestigatingParemeterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyController")
	FName TargetLocationParemeterName;

public:
	// Sets default values for this character's properties
	AEM_AIController();

	UFUNCTION()
	void SetReceiveDamage(bool bNewState) { bReceivingDamage = bNewState; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void UpdateSenses(const TArray<AActor*>& UpdatedActors);
};
