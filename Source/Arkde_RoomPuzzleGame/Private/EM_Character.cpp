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

// Sets default values
AEM_Character::AEM_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseFirstPersonView = true;
	FPSCameraSocketName = "SCK_Camera";
	MeleeSocketName = "SCK_Melee";

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
}

void AEM_Character::InitializeReferences()
{
	if (IsValid(GetMesh()))
	{
		MyAnimInstance = GetMesh()->GetAnimInstance();
	}
}

// Called every frame
void AEM_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StartAction();
	}
}

void AEM_Character::StopWeaponAction()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopAction();
	}
}

void AEM_Character::StartMelee()
{
	if (IsValid(MyAnimInstance) && IsValid(MeleeMontage))
	{
		MyAnimInstance->Montage_Play(MeleeMontage);
	}
}

void AEM_Character::StopMelee()
{
	UE_LOG(LogTemp, Warning, TEXT("Player stops melee action"));
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