// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_ExplosiveMine.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "EM_Character.h"
#include "Kismet/GameplayStatics.h"

AEM_ExplosiveMine::AEM_ExplosiveMine()
{
	ExplodeDamage = 100.0f;

	OuterColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OuterColliderComponent"));
	OuterColliderComponent->SetupAttachment(RootComponent);

	InnerColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InnerColliderComponent"));
	InnerColliderComponent->SetupAttachment(RootComponent);

	ExplosiveMineMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExplosiveMineMeshComponent"));
	ExplosiveMineMeshComponent->SetupAttachment(RootComponent);

	AlertLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("AlertLightComponent"));
	AlertLightComponent->SetIntensity(0.0f);
	AlertLightComponent->SetupAttachment(RootComponent);
}

void AEM_ExplosiveMine::BeginPlay()
{
	Super::BeginPlay();

	OuterColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AEM_ExplosiveMine::ActivateAlert);
	InnerColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AEM_ExplosiveMine::ExplodeMine);
}

void AEM_ExplosiveMine::ActivateAlert(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		AEM_Character* OverlappedCharacter = Cast<AEM_Character>(OtherActor);

		if (IsValid(OverlappedCharacter))
		{
			AlertLightComponent->SetIntensity(3000.0f);
		}
	}
}

void AEM_ExplosiveMine::ExplodeMine(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		AEM_Character* OverlappedCharacter = Cast<AEM_Character>(OtherActor);

		if (IsValid(OverlappedCharacter))
		{
			Explode();
			UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplodeDamage, GetActorLocation(), 200.0f, DamageType, TArray<AActor*>(), this, GetInstigatorController(), true, ECC_Visibility);
		}
	}
}

void AEM_ExplosiveMine::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor))
	{
		AEM_Character* OverlappedCharacter = Cast<AEM_Character>(OtherActor);

		if (IsValid(OverlappedCharacter))
		{
			AlertLightComponent->SetIntensity(0.0f);
		}
	}
}
