// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_FlameCurse.h"
#include "Kismet/GameplayStatics.h"
#include "EM_Character.h"
#include "Components/SphereComponent.h"

AEM_FlameCurse::AEM_FlameCurse()
{
	//Set default values
	ColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderComponent"));
	ColliderComponent->SetupAttachment(RootComponent);

	BurnDamage = 10.0f;
}

void AEM_FlameCurse::BeginPlay()
{
	Super::BeginPlay();

	ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AEM_FlameCurse::ApplyBurnDamage);
}

void AEM_FlameCurse::ApplyBurnDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		AEM_Character* OverlappedCharacter = Cast<AEM_Character>(OtherActor);

		if (IsValid(OverlappedCharacter) && OverlappedCharacter->GetCharacterType() == EEM_CharacterType::CharacterType_Player)
		{
			UGameplayStatics::ApplyDamage(OverlappedCharacter, BurnDamage, GetInstigatorController(), this, nullptr);
		}
	}
}
