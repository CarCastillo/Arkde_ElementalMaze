// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EM_Item.h"
#include "EM_LaunchPad.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UTextRenderComponent;
class AEM_GameMode;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_LaunchPad : public AEM_Item
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* LaunchPadColliderComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* LaunchPadMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* TextRenderComponent;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Launch Pad")
	float LaunchAngle;

public:
	// Sets default values for this actor's properties
	AEM_LaunchPad();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchPlayer(AEM_Character* CharacterToLaunch);

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Pickup(AEM_Character* CharacterToLaunch) override;

	UFUNCTION()
	void EnableLaunchPad();
};
