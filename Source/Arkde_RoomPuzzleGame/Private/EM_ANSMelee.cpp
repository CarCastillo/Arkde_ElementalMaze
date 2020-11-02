// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_ANSMelee.h"
#include "EM_Character.h"

void UEM_ANSMelee::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	 AActor* CharacterActor = MeshComp->GetOwner();

	 if (IsValid(CharacterActor))
	 {
		 AEM_Character* Character = Cast<AEM_Character>(CharacterActor);

		 if (IsValid(Character))
		 {
			 Character->SetMeleeDetectorCollision(ECollisionEnabled::QueryOnly);
		 }
	 }
}

void UEM_ANSMelee::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();

	if (IsValid(CharacterActor))
	{
		AEM_Character* Character = Cast<AEM_Character>(CharacterActor);

		if (IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::NoCollision);
		}
	}
}
