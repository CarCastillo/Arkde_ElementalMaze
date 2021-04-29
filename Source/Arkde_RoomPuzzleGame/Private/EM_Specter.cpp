// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_Specter.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EM_Character.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "DrawDebugHelpers.h"
#include "EM_HealthComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AEM_Specter::AEM_Specter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpecterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpecterMeshComponent"));
	SpecterMeshComponent->SetCanEverAffectNavigation(false);
	SpecterMeshComponent->SetSimulatePhysics(true);
	RootComponent = SpecterMeshComponent;

	SpecterParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SpecterParticleSystemComponent"));
	SpecterParticleSystemComponent->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UEM_HealthComponent>(TEXT("HealthComponent"));

	SelfDestructionDetectorComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SelfDestructionDetectorComponent"));
	SelfDestructionDetectorComponent->SetupAttachment(RootComponent);
	SelfDestructionDetectorComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SelfDestructionDetectorComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SelfDestructionDetectorComponent->SetSphereRadius(150.0f);

	MinDistanceToTarget = 100.0f;
	ForceMagnitude = 500.0f;
	ExplosionDamage = 100.0f;
	ExplosionRadius = 100.0f;
}

// Called when the game starts or when spawned
void AEM_Specter::BeginPlay()
{
	Super::BeginPlay();
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		PlayerCharacter = Cast<AEM_Character>(PlayerPawn);
	}

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AEM_Specter::TakingDamage);
	SelfDestructionDetectorComponent->OnComponentBeginOverlap.AddDynamic(this, &AEM_Specter::StartCountdown);

	BotMaterial = SpecterMeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, SpecterMeshComponent->GetMaterial(0));

	NextPathPoint = GetNextPathPoint();

	SpecterParticleSystemComponent = UGameplayStatics::SpawnEmitterAttached(SmogEffect, RootComponent);
}

FVector AEM_Specter::GetNextPathPoint()
{
	if (!IsValid(PlayerCharacter))
	{
		return GetActorLocation();
	}

	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(), GetActorLocation(), PlayerCharacter);

	if (NavigationPath->PathPoints.Num() > 1)
	{
		return NavigationPath->PathPoints[1];
	}

	return GetActorLocation();
}

void AEM_Specter::TakingDamage(UEM_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsValid(BotMaterial))
	{
		BotMaterial->SetScalarParameterValue("Pulse", GetWorld()->TimeSeconds);
	}

	if (CurrentHealthComponent->IsDead())
	{
		SelfDestruction();
	}
}

void AEM_Specter::SelfDestruction()
{
	if (bIsExploded)
	{
		return;
	}

	bIsExploded = true;

	if (IsValid(ExplosionEffect))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	}

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplosionDamage, GetActorLocation(), ExplosionRadius, nullptr, IgnoredActors, this, GetInstigatorController(), true);

	if (bDebug)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionRadius, 20, FColor::Red, true, 5.0f, 0, 2.0f);
	}

	Destroy();
}

void AEM_Specter::StartCountdown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsStartingCountdown)
	{
		return;
	}

	if (OtherActor == PlayerCharacter)
	{
		bIsStartingCountdown = true;

		GetWorldTimerManager().SetTimer(SelfDamageTimer, this, &AEM_Specter::SelfDamage, 0.5f, true);
	}

}

void AEM_Specter::SelfDamage()
{
	UGameplayStatics::ApplyDamage(this, 20.0f, GetInstigatorController(), nullptr, nullptr);
}

// Called every frame
void AEM_Specter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DistanceToTarget = (GetActorLocation() - NextPathPoint).Size();

	if (DistanceToTarget <= MinDistanceToTarget)
	{
		NextPathPoint = GetNextPathPoint();
	}
	else
	{
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= ForceMagnitude;

		SpecterMeshComponent->AddForce(ForceDirection, NAME_None, true);
	}

	if (bDebug)
	{
		DrawDebugSphere(GetWorld(), NextPathPoint, 30.0f, 10, FColor::Purple, false, 0.0f, 0, 1.0f);
	}
	
}

