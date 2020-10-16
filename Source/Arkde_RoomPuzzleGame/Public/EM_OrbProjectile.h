// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EM_OrbProjectile.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class USphereComponent;
class ACharacter;
class UDamageType;

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_OrbProjectile : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* OrbProjectileCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* OrbProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* OrbProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* ExplodeEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Orb Launcher")
	float OrbExplodeDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Orb Launcher")
	float OrbDestroyDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Orb Launcher")
	float OrbDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	AActor* OwnerWeapon;
	
public:	
	// Sets default values for this actor's properties
	AEM_OrbProjectile();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void SetOwnerWeapon(AActor* NewOwner) { OwnerWeapon = NewOwner; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ExplodeOrbProjectile();

	void DestroyOrbProjectile();

	FTimerHandle OrbExplodeTimer;

	FTimerHandle OrbDestroyTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
