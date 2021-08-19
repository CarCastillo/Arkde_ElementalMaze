// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_MiasmaBarrel.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EM_Character.h"
#include "EM_Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "EM_HealthComponent.h"
#include "Sound/SoundCue.h"

AEM_MiasmaBarrel::AEM_MiasmaBarrel()
{
	BarrelDestroyTime = 3.0f;

	BarrelColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BarrelColliderComponent"));
	BarrelColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BarrelColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BarrelColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	BarrelColliderComponent->SetupAttachment(RootComponent);

	MiasmaColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MiasmaColliderComponent"));
	MiasmaColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MiasmaColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MiasmaColliderComponent->SetupAttachment(RootComponent);

	BarrelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMeshComponent"));
	BarrelMeshComponent->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UEM_HealthComponent>(TEXT("HealthComponent"));
}

void AEM_MiasmaBarrel::BeginPlay()
{
	Super::BeginPlay();

	MiasmaColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AEM_MiasmaBarrel::SpreadMiasma);
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AEM_MiasmaBarrel::OnHealthChange);
}

void AEM_MiasmaBarrel::OnHealthChange(UEM_HealthComponent* MyHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (HealthComponent->IsDead())
	{
		if (IsValid(ExplosionSound))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
		}

		SetExplosionEffect(BarrelDestroyTime);
		MiasmaColliderComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	}
}

void AEM_MiasmaBarrel::SpreadMiasma(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		AEM_Character* OverlappedCharacter = Cast<AEM_Character>(OtherActor);

		if (IsValid(OverlappedCharacter) && OverlappedCharacter->GetCharacterType() == EEM_CharacterType::CharacterType_Player)
		{
			OverlappedCharacter->SetPoisonStatusEffect();
			DrawDebugSphere(GetWorld(), CustomRootComponent->GetComponentLocation(), 300.0f, 32, FColor::Red, false, 2.0f);
		}
	}
}
