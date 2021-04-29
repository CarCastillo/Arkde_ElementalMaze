// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EM_Specter.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
class AEM_Character;
class UEM_HealthComponent;
class USphereComponent;

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_Specter : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SpecterMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SelfDestructionDetectorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* SpecterParticleSystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UEM_HealthComponent* HealthComponent;

public:
	// Sets default values for this pawn's properties
	AEM_Specter();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle Effects")
	UParticleSystem* SmogEffect;

	UPROPERTY(BlueprintReadOnly, Category = "Bot")
	FVector NextPathPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
	bool bDebug;

	UPROPERTY(BlueprintReadOnly, Category = "Bot Self Destruction")
	bool bIsExploded;

	UPROPERTY(BlueprintReadOnly, Category = "Bot Self Destruction")
	bool bIsStartingCountdown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Movement")
	float MinDistanceToTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Movement")
	float ForceMagnitude;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Effects")
	float ExplosionDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Effects")
	float ExplosionRadius;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	AEM_Character* PlayerCharacter;

	UMaterialInstanceDynamic* BotMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Effects")
	UParticleSystem* ExplosionEffect;

	FTimerHandle SelfDamageTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	FVector GetNextPathPoint();

	UFUNCTION()
	void TakingDamage(UEM_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	void SelfDestruction();

	UFUNCTION()
	void StartCountdown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SelfDamage();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
