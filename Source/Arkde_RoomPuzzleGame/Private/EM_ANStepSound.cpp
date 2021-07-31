// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_ANStepSound.h"
#include "EM_Character.h"

void UEM_ANStepSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();

	if (IsValid(CharacterActor))
	{
		AEM_Character* Character = Cast<AEM_Character>(CharacterActor);

		if (IsValid(Character))
		{
			Character->PlayStepSound();
		}
	}
}