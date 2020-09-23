// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_OrbLauncher.h"
#include "EM_OrbProjectile.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

AEM_OrbLauncher::AEM_OrbLauncher()
{
	MuzzleSocketName = "SCK_Muzzle";
}

void AEM_OrbLauncher::StartAction()
{
	Super::StartAction();

	USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();

	if (IsValid(CurrentOwnerCharacter))
	{
		if (IsValid(CharacterMeshComponent))
		{
			FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
			FRotator MuzzleSocketRotation = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);

			AEM_OrbProjectile* CurrentOrbProjectile = GetWorld()->SpawnActor<AEM_OrbProjectile>(OrbProjectileClass, MuzzleSocketLocation, MuzzleSocketRotation);
		}
	}
}

void AEM_OrbLauncher::StopAction()
{
	Super::StopAction();
}
