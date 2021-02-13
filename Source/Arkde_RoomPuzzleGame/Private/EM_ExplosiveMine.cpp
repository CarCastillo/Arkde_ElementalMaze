// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_ExplosiveMine.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "EM_Character.h"
#include "EM_Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "EM_HealthComponent.h"

AEM_ExplosiveMine::AEM_ExplosiveMine()
{
	ExplodeDamage = 100.0f;
	MineDestroyTime = 1.0f;

	OuterColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OuterColliderComponent"));
	OuterColliderComponent->SetupAttachment(RootComponent);

	InnerColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InnerColliderComponent"));
	InnerColliderComponent->SetupAttachment(RootComponent);

	ExplosiveMineMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExplosiveMineMeshComponent"));
	ExplosiveMineMeshComponent->SetupAttachment(RootComponent);

	AlertLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("AlertLightComponent"));
	AlertLightComponent->SetIntensity(0.0f);
	AlertLightComponent->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UEM_HealthComponent>(TEXT("HealthComponent"));
}

void AEM_ExplosiveMine::BeginPlay()
{
	Super::BeginPlay();

	OuterColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AEM_ExplosiveMine::ActivateAlert);
	InnerColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AEM_ExplosiveMine::ExplodeMine);
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AEM_ExplosiveMine::OnHealthChange);
}

void AEM_ExplosiveMine::OnHealthChange(UEM_HealthComponent* MyHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (HealthComponent->IsDead())
	{
		SetExplosionEffect(MineDestroyTime);
	}
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
			SetExplosionEffect(MineDestroyTime);
			DrawDebugSphere(GetWorld(), CustomRootComponent->GetComponentLocation(), 200.0f, 32, FColor::Red, false, 2.0f);
			UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplodeDamage, GetActorLocation(), 200.0f, nullptr, TArray<AActor*>(), this, GetInstigatorController(), true, ECC_Visibility);
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
