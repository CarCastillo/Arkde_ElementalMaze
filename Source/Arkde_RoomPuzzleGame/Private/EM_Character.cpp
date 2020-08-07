// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_Character.h"

// Sets default values
AEM_Character::AEM_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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


void AEM_Character::AddControllerPitchInput(float value)
{
	Super::AddControllerPitchInput(bIsLookInversion ? -value : value);
}