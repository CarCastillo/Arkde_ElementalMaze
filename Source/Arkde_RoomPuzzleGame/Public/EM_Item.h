// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EM_Item.generated.h"

class USphereComponent;
class AEM_Character;
class AEM_GameMode;
class USoundCue;

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_Item : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* MainColliderComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundCue* PickupSound;

protected:

	UPROPERTY(BlueprintReadOnly)
	AEM_GameMode* GameModeReference;

public:	
	// Sets default values for this actor's properties
	AEM_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Pickup(AEM_Character* PickupCharacter);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	void BP_Pickup(AEM_Character* PickupCharacter);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
