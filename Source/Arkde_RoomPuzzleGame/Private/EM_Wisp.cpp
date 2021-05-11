// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_Wisp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EM_Character.h"
#include "EM_Enemy.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "DrawDebugHelpers.h"
#include "EM_HealthComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AEM_Wisp::AEM_Wisp()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WispMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WispMeshComponent"));
	WispMeshComponent->SetCanEverAffectNavigation(false);
	WispMeshComponent->SetSimulatePhysics(true);
	RootComponent = WispMeshComponent;

	HealthComponent = CreateDefaultSubobject<UEM_HealthComponent>(TEXT("HealthComponent"));

	ColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderComponent"));
	ColliderComponent->SetupAttachment(RootComponent);
	ColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	ColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ColliderComponent->SetSphereRadius(100.0f);

	MinDistanceToTarget = 100.0f;
	ForceMagnitude = 500.0f;

}

// Called when the game starts or when spawned
void AEM_Wisp::BeginPlay()
{
	Super::BeginPlay();
	
	NextPathPoint = GetNextPathPoint();
	GetWorldTimerManager().SetTimer(EnemyDamageDetectionTimer, this, &AEM_Wisp::VerifyEnemyHealth, 0.2f, true);
	ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AEM_Wisp::HealDamagedEnemy);
}

FVector AEM_Wisp::GetNextPathPoint()
{
	FVector RandomPoint = UNavigationSystemV1::GetRandomPointInNavigableRadius(GetWorld(), GetActorLocation(), 250.0f);
	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), GetActorLocation(), RandomPoint);

	if (NavigationPath->PathPoints.Num() > 1)
	{
		return NavigationPath->PathPoints[1];
	}

	return GetActorLocation();
}

bool AEM_Wisp::IsEnemyDamaged()
{
	TArray<AActor*> EnemiesList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEM_Enemy::StaticClass(), EnemiesList);

	if (EnemiesList.Num())
	{
		for (auto& Enemy : EnemiesList)
		{
			if (IsValid(Enemy))
			{
				DamagedEnemy = Cast<AEM_Enemy>(Enemy);
				if (IsValid(DamagedEnemy))
				{
					if (DamagedEnemy->bIsDamaged)
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "ENEMY DAMAGED!");
						DamagedEnemiesList.Push(DamagedEnemy);
					}
				}
			}
		}
	}

	return DamagedEnemiesList.Num() > 0;
}

void AEM_Wisp::VerifyEnemyHealth()
{
	IsEnemyDamaged();

	if (IsEnemyDamaged())
	{
		MoveToEnemyLocation();
	}
}

void AEM_Wisp::MoveToEnemyLocation()
{
	NextPathPoint = DamagedEnemiesList[0]->GetActorLocation();
}

void AEM_Wisp::HealDamagedEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsEnemyDamaged())
	{
		return;
	}

	if (DamagedEnemiesList.Num() > 0)
	{
		if (DamagedEnemiesList.Contains(OtherActor))
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, "Healing Time!");
	}

}

// Called every frame
void AEM_Wisp::Tick(float DeltaTime)
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

		WispMeshComponent->AddForce(ForceDirection, NAME_None, true);
	}
}

