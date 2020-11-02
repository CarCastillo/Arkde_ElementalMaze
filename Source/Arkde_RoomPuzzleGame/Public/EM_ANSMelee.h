// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EM_ANSMelee.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLEGAME_API UEM_ANSMelee : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;
};
