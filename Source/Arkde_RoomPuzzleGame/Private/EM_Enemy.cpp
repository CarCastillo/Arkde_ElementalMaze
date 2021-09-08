// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_Enemy.h"
#include "EM_HealthComponent.h"
#include "EM_Character.h"
#include "EM_Weapon.h"
#include "Components/CapsuleComponent.h"
#include "EM_Item.h"
#include "EM_MagicProjectile.h"
#include "AIModule/Classes/Perception/AISense_Damage.h"
#include "EM_AIController.h"
#include "EM_FlameCurse.h"
#include "EM_GameInstance.h"
#include "Components/WidgetComponent.h"
#include "EM_EnemyHealthBar.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "EM_GameMode.h"

AEM_Enemy::AEM_Enemy() 
{
	bLoopPath = false;
	DirectionIndex = 1;
	WaitingTimeOnPathPoint = 1.0f;
	XPValue = 40.0f;
	LootProbability = 100.0f;

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);
}

void AEM_Enemy::BeginPlay()
{
	Super::BeginPlay();

	MyAIController = Cast<AEM_AIController>(GetController());

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AEM_Enemy::HealthChange);
	HealthComponent->OnDeadDelegate.AddDynamic(this, &AEM_Enemy::GiveXP);

	UUserWidget* WidgetObject = HealthBarWidgetComponent->GetUserWidgetObject();
	if (IsValid(WidgetObject))
	{
		EnemyHealthBar = Cast<UEM_EnemyHealthBar>(WidgetObject);

		if (IsValid(EnemyHealthBar))
		{
			HealthComponent->OnHealthUpdateDelegate.AddDynamic(EnemyHealthBar, &UEM_EnemyHealthBar::UpdateHealth);
			HideHealthBar();
		}
	}
}

void AEM_Enemy::GiveXP(AActor* DamageCauser)
{
	AEM_Character* PossiblePlayer = Cast<AEM_Character>(DamageCauser);

	if (IsValid(PossiblePlayer) && PossiblePlayer->GetCharacterType() == EEM_CharacterType::CharacterType_Player)
	{
		PossiblePlayer->GainUltimateXP(XPValue);
		TrySpawnLoot();
	}

	AEM_Weapon* PossibleWeapon = Cast<AEM_Weapon>(DamageCauser);

	if (IsValid(PossibleWeapon))
	{
		AEM_Character* WeaponOwner = Cast<AEM_Character>(PossibleWeapon->GetOwner());

		if (IsValid(WeaponOwner) && WeaponOwner->GetCharacterType() == EEM_CharacterType::CharacterType_Player)
		{
			WeaponOwner->GainUltimateXP(XPValue);
			TrySpawnLoot();
		}
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StopWeaponAction();

	BP_GiveXP(DamageCauser);
}

bool AEM_Enemy::TrySpawnLoot()
{
	if (!IsValid(LootItemClass))
	{
		return false;
	}

	float SelectedProbability = FMath::RandRange(0.0f, 100.0f);

	if (SelectedProbability <= LootProbability)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AEM_Item>(LootItemClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);
	}

	return true;
}

void AEM_Enemy::HealthChange(UEM_HealthComponent* CurrentHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!IsValid(MyAIController))
	{
		return;
	}

	if (bIsShowingHealthBar)
	{
		GetWorld()->GetTimerManager().ClearTimer(HideHealthBarTimer); 
	}
	else
	{
		ShowHealthBar();
	}

	GetWorld()->GetTimerManager().SetTimer(HideHealthBarTimer, this, &AEM_Enemy::HideHealthBar, 1.0f, false);

	if (CurrentHealthComponent->IsOnCriticalStatus())
	{
		FVector DamageCauserLocation = DamageCauser->GetActorLocation();
		AEM_Character* PlayerCharacter = Cast<AEM_Character>(DamageCauser);

		// cast flames (TODO: attack based on enemy elemental type)
		// TODO: validate player is not using ultimate (get projectile owner) OR set bool during stun status
		CastFlames(DamageCauserLocation);

		if (IsValid(ElementalAttackSound))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ElementalAttackSound, DamageCauserLocation);
		}
	}

	if (CurrentHealthComponent->IsDead())
	{
		MyAIController->UnPossess();

		if (IsValid(GameInstanceReference))
		{
			GameInstanceReference->AddEnemyDefeatedToCounter();
		}

		if (IsValid(GameModeReference))
		{
			GameModeReference->VerifyEnemiesDefeated(this);
		}

		HideHealthBar();
	}
	else
	{
		AEM_MagicProjectile* MagicProjectile = Cast<AEM_MagicProjectile>(DamageCauser);
		if (IsValid(MagicProjectile))
		{
			AActor* MagicProjectileOwner = MagicProjectile->GetOwner();
			MyAIController->SetReceiveDamage(true);
			UAISense_Damage::ReportDamageEvent(GetWorld(), this, MagicProjectileOwner, Damage, MagicProjectileOwner->GetActorLocation(), FVector::ZeroVector);
		}
	}
}

void AEM_Enemy::CastFlames(FVector TargetLocation)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AEM_FlameCurse>(FlameCurseClass, TargetLocation, FRotator::ZeroRotator, SpawnParameters);
}

void AEM_Enemy::ShowHealthBar()
{
	bIsShowingHealthBar = true;
	EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);
}

void AEM_Enemy::HideHealthBar()
{
	bIsShowingHealthBar = false;
	EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
}
