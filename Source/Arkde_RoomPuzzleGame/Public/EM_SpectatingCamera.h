// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EM_SpectatingCamera.generated.h"

class UStaticMeshComponent;

UENUM(Blueprintable)
enum class EEM_SpectatingCameraType : uint8
{
	CameraType_None		UMETA(DisplayName = "None"),
	CameraType_Victory	UMETA(DisplayName = "Victory"),
	CameraType_GameOver	UMETA(DisplayName = "GameOver")
};

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_SpectatingCamera : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SpectatingCameraComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spectating Camera")
	EEM_SpectatingCameraType CameraType;
	
public:	
	// Sets default values for this actor's properties
	AEM_SpectatingCamera();

	EEM_SpectatingCameraType GetCameraType() { return CameraType; };
};
