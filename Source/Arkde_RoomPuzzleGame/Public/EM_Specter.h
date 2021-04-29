// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EM_Specter.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
class UParticleSystem;
class AEM_Character;
class UEM_HealthComponent;
class UMaterialInstanceDynamic;

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_Specter : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SpecterMeshComponent;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Movement")
	float MinDistanceToTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bot Movement")
	float ForceMagnitude;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	AEM_Character* PlayerCharacter;

	UMaterialInstanceDynamic* BotMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	FVector GetNextPathPoint();

	UFUNCTION()
	void TakingDamage(UEM_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
