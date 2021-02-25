// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EM_Dummy.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class UParticleSystemComponent;

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_Dummy : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "My Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "My Components")
	USkeletalMeshComponent* DummyMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "My Components")
	UCapsuleComponent* CapsuleColliderComponent;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "My Components")
	UParticleSystemComponent* EffectStatusParticleSystemComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsGoingRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float dummySpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float leftMovementDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float rightMovementDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Status Effects")
	UParticleSystem* StunEffect;

public:
	bool bIsDummyOnMovement;

public:	
	// Sets default values for this actor's properties
	AEM_Dummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Move();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
