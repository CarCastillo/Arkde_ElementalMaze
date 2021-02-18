// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_Character.h"
#include "Arkde_RoomPuzzleGame/Arkde_RoomPuzzleGame.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EM_LaunchPad.h"
#include "EM_Weapon.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EM_HealthComponent.h"
#include "EM_GameMode.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AEM_Character::AEM_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseFirstPersonView = true;
	FPSCameraSocketName = "SCK_Camera";
	MeleeDamage = 10.0f;
	MeleeSocketName = "SCK_Melee";
	bCanUseProjectile = true;
	MaxNumComboMultiplier = 4.0f;
	CurrentNumComboMultiplier = 1.0f;
	FakeWallDestroyDelay = 3.0f;
	ForceOfImpulse = 2000000.0f;
	MaxUltimateXP = 100.0f;
	MaxUltimateDuration = 10.0f;
	bUltimateWithTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_CameraComponent"));
	FPSCameraComponent->bUsePawnControlRotation = true;
	FPSCameraComponent->SetupAttachment(GetMesh(), FPSCameraSocketName);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_CameraComponent"));
	TPSCameraComponent->SetupAttachment(SpringArmComponent);

	MeleeDetectorComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeDetectorComponent"));
	MeleeDetectorComponent->SetupAttachment(GetMesh(), MeleeSocketName);
	MeleeDetectorComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeDetectorComponent->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);
	MeleeDetectorComponent->SetCollisionResponseToChannel(ECC_Destructible, ECR_Overlap);
	MeleeDetectorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthComponent = CreateDefaultSubobject<UEM_HealthComponent>(TEXT("HealthComponent"));

	EffectStatusParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BeamComp"));
	EffectStatusParticleSystemComponent->SetupAttachment(RootComponent);
	EffectStatusParticleSystemComponent->bAutoActivate = false;
}

FVector AEM_Character::GetPawnViewLocation() const
{
	if (IsValid(FPSCameraComponent) && bUseFirstPersonView)
	{
		return FPSCameraComponent->GetComponentLocation();
	}

	if (IsValid(TPSCameraComponent) && !bUseFirstPersonView)
	{
		return TPSCameraComponent->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}

// Called when the game starts or when spawned
void AEM_Character::BeginPlay()
{
	Super::BeginPlay();

	InitializeReferences();
	CreateInitialWeapon();

	MeleeDetectorComponent->OnComponentBeginOverlap.AddDynamic(this, &AEM_Character::MakeMeleeDamage);
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AEM_Character::OnHealthChange);
}

void AEM_Character::InitializeReferences()
{
	if (IsValid(GetMesh()))
	{
		MyAnimInstance = GetMesh()->GetAnimInstance();
	}

	GameModeReference = Cast<AEM_GameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AEM_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bUltimateWithTick && bIsUsingUltimate)
	{
		UpdateUltimateDuration(DeltaTime);
	}
}

// Called to bind functionality to input
void AEM_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AEM_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEM_Character::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AEM_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &ACharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEM_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AEM_Character::StopJumping);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AEM_Character::StartCrouch);

	PlayerInputComponent->BindAction("Activate", IE_Pressed, this, &AEM_Character::ActivateLaunchPad);

	PlayerInputComponent->BindAction("WeaponAction", IE_Pressed, this, &AEM_Character::StartWeaponAction);
	PlayerInputComponent->BindAction("WeaponAction", IE_Released, this, &AEM_Character::StopWeaponAction);

	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &AEM_Character::StartMelee);
	PlayerInputComponent->BindAction("Melee", IE_Released, this, &AEM_Character::StopMelee);

	PlayerInputComponent->BindAction("Ultimate", IE_Pressed, this, &AEM_Character::StartUltimate);
	PlayerInputComponent->BindAction("Ultimate", IE_Pressed, this, &AEM_Character::StopUltimate);
}

void AEM_Character::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * value);
}

void AEM_Character::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void AEM_Character::Jump()
{
	Super::Jump();

}
void AEM_Character::StopJumping()
{
	Super::StopJumping();
}

void AEM_Character::StartCrouch()
{
	if (!GetCharacterMovement()->IsCrouching())
	{
		Crouch(false);
	}
	else
	{
		UnCrouch(false);
	}
}

void AEM_Character::Crouch(bool bClientSimulation)
{
	Super::Crouch();
}

void AEM_Character::UnCrouch(bool bClientSimulation)
{
	Super::UnCrouch();
}

void AEM_Character::CreateInitialWeapon()
{
	if (IsValid(InitialWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<AEM_Weapon>(InitialWeaponClass, GetActorLocation(), GetActorRotation());

		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetCharacterOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

void AEM_Character::StartWeaponAction()
{
	if (!bCanUseProjectile)
	{
		return;
	}

	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StartAction();
	}
}

void AEM_Character::StopWeaponAction()
{
	if (!bCanUseProjectile)
	{
		return;
	}

	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopAction();
	}
}

void AEM_Character::StartMelee()
{
	if (bIsDoingMelee && !bCanMakeCombos)
	{
		return;
	}

	if (bCanMakeCombos)
	{
		if (bIsDoingMelee)
		{
			if (bIsComboEnabled)
			{
				if (CurrentNumComboMultiplier < MaxNumComboMultiplier)
				{
					CurrentNumComboMultiplier++;
					SetComboEnabled(false);
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
		}
	}

	if (IsValid(MyAnimInstance) && IsValid(MeleeMontage))
	{
		MyAnimInstance->Montage_Play(MeleeMontage);
	}

	SetMeleeState(true);
}

void AEM_Character::StopMelee()
{
	// UE_LOG(LogTemp, Warning, TEXT("Player stops melee action"));
}

void AEM_Character::DestroyFakeWall(AActor* DestructibleActor)
{
	GetWorldTimerManager().ClearTimer(FakeWallDestroyTimer);
	DestructibleActor->Destroy();
}

void AEM_Character::MakeMeleeDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		UStaticMeshComponent* OtherActorMeshComp = nullptr;
		OtherActorMeshComp = Cast<UStaticMeshComponent>(OtherActor->GetRootComponent());

		if (IsValid(OtherActorMeshComp))
		{
			if (OtherActorMeshComp->GetCollisionObjectType() == ECollisionChannel::ECC_Destructible)
			{
				OtherActorMeshComp->SetSimulatePhysics(true);
				OtherActorMeshComp->AddImpulse(GetActorForwardVector() * ForceOfImpulse);
				FakeWallTimerDel = FTimerDelegate::CreateUObject(this, &AEM_Character::DestroyFakeWall, OtherActor);
				GetWorldTimerManager().SetTimer(FakeWallDestroyTimer, FakeWallTimerDel, FakeWallDestroyDelay, true);
			}
		}

		UGameplayStatics::ApplyPointDamage(OtherActor, MeleeDamage * CurrentNumComboMultiplier, SweepResult.Location, SweepResult, GetInstigatorController(), this, nullptr);	
	}
}

void AEM_Character::OnHealthChange(UEM_HealthComponent* MyHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (HealthComponent->IsDead())
	{
		if (IsValid(GameModeReference))
		{
			GameModeReference->GameOver(this);
		}
	}
}

void AEM_Character::AddControllerPitchInput(float value)
{
	Super::AddControllerPitchInput(bIsLookInversion ? -value : value);
}

void AEM_Character::AddKey(FName NewKey)
{
	DoorKeys.Add(NewKey);
}

bool AEM_Character::HasKey(FName KeyTag)
{
	return DoorKeys.Contains(KeyTag);
}

void AEM_Character::ActivateLaunchPad()
{
	if (IsValid(CurrentLaunchPad))
	{
		CurrentLaunchPad->LaunchPlayer(this);
	}
}

void AEM_Character::SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState)
{
	MeleeDetectorComponent->SetCollisionEnabled(NewCollisionState);
}

void AEM_Character::SetMeleeState(bool NewState)
{
	bIsDoingMelee = NewState;
	bCanUseProjectile = !NewState;
}

void AEM_Character::SetPoisonStatusEffect()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Character has been poisoned!");
	EffectStatusParticleSystemComponent = UGameplayStatics::SpawnEmitterAttached(PoisonEffect, RootComponent);
	GetWorldTimerManager().SetTimer(StatusEffectTimer, this, &AEM_Character::RemovePoisonStatusEffect, 5.0f, true);
	GetWorldTimerManager().SetTimer(StatusEffectDPSTimer, this, &AEM_Character::MakeDamagePerSecond, 1.0f, true);
}

void AEM_Character::RemovePoisonStatusEffect()
{
	GetWorldTimerManager().ClearTimer(StatusEffectTimer);
	GetWorldTimerManager().ClearTimer(StatusEffectDPSTimer);
	EffectStatusParticleSystemComponent->Deactivate();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Character is not poisoned anymore!");
}

void AEM_Character::MakeDamagePerSecond()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, "Character received 10 damage!");
	AActor::TakeDamage(10.0f, FDamageEvent(), GetInstigatorController(), nullptr);
}

void AEM_Character::StartUltimate()
{
	if (bCanUseUltimate && !bIsUsingUltimate) 
	{
		CurrentUltimateDuration = MaxUltimateDuration;

		bCanUseUltimate = false;
		bIsUsingUltimate = true;
		BP_StartUltimate();
	}
}

void AEM_Character::StopUltimate()
{
}

void AEM_Character::SetComboEnabled(bool NewState)
{
	bIsComboEnabled = NewState;
}

void AEM_Character::ResetCombo()
{
	SetComboEnabled(false);
	CurrentNumComboMultiplier = 1.0f;
}

void AEM_Character::GainUltimateXP(float XPGained)
{
	if (bCanUseUltimate || bIsUsingUltimate)
	{
		return;
	}

	CurrentUltimateXP = FMath::Clamp(CurrentUltimateXP + XPGained, 0.0f, MaxUltimateXP);

	if (CurrentUltimateXP == MaxUltimateXP)
	{
		bCanUseUltimate = true;
	}

	BP_GainUltimateXP(XPGained);
}

void AEM_Character::UpdateUltimateDuration(float Value)
{
	CurrentUltimateDuration = FMath::Clamp(CurrentUltimateDuration - Value, 0.0f, MaxUltimateDuration);
	BP_UpdateUltimateDuration(Value);

	if (CurrentUltimateDuration == 0.0f)
	{
		bIsUsingUltimate = false;
		BP_StopUltimate();
	}
}
