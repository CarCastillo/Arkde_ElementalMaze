// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_ANEnableAction.h"
#include "EM_Character.h"

void UEM_ANEnableAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();

	if (IsValid(CharacterActor))
	{
		AEM_Character* Character = Cast<AEM_Character>(CharacterActor);

		if (IsValid(Character))
		{
			Character->SetMeleeState(false);
		}
	}
}
