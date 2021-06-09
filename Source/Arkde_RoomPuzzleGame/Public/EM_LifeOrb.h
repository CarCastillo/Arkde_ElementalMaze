// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EM_Item.h"
#include "EM_LifeOrb.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_LifeOrb : public AEM_Item
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* LifeOrbMeshComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float HealthValue;

public:
	// Sets default values for this actor's properties
	AEM_LifeOrb();

public:

	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetHealthValue() const { return HealthValue; };

protected:

	virtual void Pickup(AEM_Character* PickupCharacter) override;
	
};
