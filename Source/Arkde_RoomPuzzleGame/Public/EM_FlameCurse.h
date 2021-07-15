// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EM_ElementalCurse.h"
#include "EM_FlameCurse.generated.h"

class USphereComponent;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_FlameCurse : public AEM_ElementalCurse
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* ColliderComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float BurnDamage;

public:
	// Sets default values for this actor's properties
	AEM_FlameCurse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void ApplyBurnDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
