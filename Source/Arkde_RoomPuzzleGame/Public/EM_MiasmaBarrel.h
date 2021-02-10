// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EM_MazeTrap.h"
#include "EM_MiasmaBarrel.generated.h"

class UBoxComponent;
class USphereComponent;
class UStaticMeshComponent;
class UEM_HealthComponent;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_MiasmaBarrel : public AEM_MazeTrap
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BarrelColliderComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* MiasmaColliderComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BarrelMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UEM_HealthComponent* HealthComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	float BarrelDestroyTime;
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHealthChange(UEM_HealthComponent* MyHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:

	AEM_MiasmaBarrel();

	UFUNCTION()
	void SpreadMiasma(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

