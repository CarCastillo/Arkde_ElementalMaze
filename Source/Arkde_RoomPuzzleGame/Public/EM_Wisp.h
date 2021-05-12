// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EM_Wisp.generated.h"

class UStaticMeshComponent;
class AEM_Character;
class AEM_Enemy;
class UEM_HealthComponent;
class USphereComponent;
class UParticleSystem;

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_Wisp : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* WispMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* ColliderComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UEM_HealthComponent* HealthComponent;

public:
	// Sets default values for this pawn's properties
	AEM_Wisp();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Bot")
	FVector NextPathPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Movement")
	float MinDistanceToTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Movement")
	float ForceMagnitude;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Healing")
	float HealingPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
	bool bDebug;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	AEM_Enemy* EnemyPawn;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	AEM_Enemy* DamagedEnemy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particles")
	UParticleSystem* HealingEffect;

	TArray<AEM_Enemy*> DamagedEnemiesList;

	FTimerHandle EnemyDamageDetectionTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	FVector GetNextPathPoint();

	bool IsEnemyDamaged();

	void VerifyEnemyHealth();

	void MoveToEnemyLocation();

	UFUNCTION()
	void HealDamagedEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
