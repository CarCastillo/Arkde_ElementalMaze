// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EM_Item.h"
#include "EM_LaunchPad.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_LaunchPad : public AEM_Item
{
	GENERATED_BODY()

protected:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* LaunchPadColliderComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* LaunchPadMeshComponent;

public:
	// Sets default values for this actor's properties
	AEM_LaunchPad();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void Pickup(AEM_Character* CharacterToLaunch) override;
};
