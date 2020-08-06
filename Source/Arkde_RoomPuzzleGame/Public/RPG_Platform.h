// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPG_Platform.generated.h"

class UStaticMeshComponent;

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API ARPG_Platform : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "My Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "My Components")
	UStaticMeshComponent* PlatformMeshComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	bool bIsGoingUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float minHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float maxHeight;
	
public:	
	// Sets default values for this actor's properties
	ARPG_Platform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Move();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
