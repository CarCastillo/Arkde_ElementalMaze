// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EM_LaunchPad.h"

// Sets default values
AEM_Character::AEM_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseFirstPersonView = true;
	bIsLaunchPadActivated = false;
	FPSCameraSocketName = "SCK_Camera";

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_CameraComponent"));
	FPSCameraComponent->bUsePawnControlRotation = true;
	FPSCameraComponent->SetupAttachment(GetMesh(), FPSCameraSocketName);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_CameraComponent"));
	TPSCameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AEM_Character::BeginPlay()
{
	Super::BeginPlay();
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
	UE_LOG(LogTemp, Warning, TEXT("IT'S CROUCH TIME"));
	Super::Crouch();
}

void AEM_Character::UnCrouch(bool bClientSimulation)
{
	UE_LOG(LogTemp, Warning, TEXT("IT'S UNCROUCH TIME"));
	Super::UnCrouch();
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
	bIsLaunchPadActivated = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LAUNCH PAD ACTIVATED!."));
}