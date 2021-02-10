// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EM_MazeTrap.generated.h"

class USceneComponent;
class AEM_Character;
class UParticleSystem;

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_MazeTrap : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* ExplodeEffect;

protected:

	FTimerHandle TrapDestroyTimer;
	
public:	
	// Sets default values for this actor's properties
	AEM_MazeTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Explode();

	void DestroyTrap();
};
