// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EM_MazeTrap.h"
#include "GameFramework/Actor.h"
#include "EM_ExplosiveMine.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UPointLightComponent;
class UParticleSystem;
class UEM_HealthComponent;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_ExplosiveMine : public AEM_MazeTrap
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* OuterColliderComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* InnerColliderComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ExplosiveMineMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPointLightComponent* AlertLightComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UEM_HealthComponent* HealthComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosive Mine")
	float ExplodeDamage;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHealthChange(UEM_HealthComponent* MyHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:

	AEM_ExplosiveMine();

	UFUNCTION()
	void ActivateAlert(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ExplodeMine(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
