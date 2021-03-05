// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EM_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class AEM_LaunchPad;
class AEM_Weapon;
class UAnimMontage;
class UAnimInstance;
class UEM_HealthComponent;
class AEM_GameMode;
class UParticleSystem;
class UParticleSystemComponent;
class AEM_Dummy;

UENUM(Blueprintable)
enum class EEM_CharacterType : uint8
{
	CharacterType_Player	UMETA(DisplayName = "Player"),
	CharacterType_Enemy		UMETA(DisplayName = "Enemy")
};

UCLASS()
class ARKDE_ROOMPUZZLEGAME_API AEM_Character : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* FPSCameraComponent; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* TPSCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* MeleeDetectorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UEM_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* EffectStatusParticleSystemComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
	bool bUseFirstPersonView;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming") 
	bool bIsLookInversion;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
	FName FPSCameraSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	bool bCanMakeCombos;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsComboEnabled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Over")
	bool bHasToDestroy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee", meta = (EditCondition = bCanMakeCombos, ClampMin = 1.0, UIMin = 1.0))
	float MaxNumComboMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee", meta = (EditCondition = bCanMakeCombos, ClampMin = 1.0, UIMin = 1.0))
	float CurrentNumComboMultiplier;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float MeleeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timers")
	float FakeWallDestroyDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Impulse")
	float ForceOfImpulse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate", meta = (ClampMin = 0.0f, UIMin = 0.0))
	float MaxUltimateXP;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
	float CurrentUltimateXP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate|Time", meta = (ClampMin = 0.0f, UIMin = 0.0))
	float MaxUltimateDuration;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate|Time")
	float CurrentUltimateDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate|Time")
	float UltimateFrequency;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate|Time", meta = (ClampMin = 0.0f, UIMin = 0.0))
	float UltimatePlayRate;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate|Time")
	float PlayRate;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsDoingMelee;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	bool bCanUseProjectile;

	UPROPERTY(EditDefaultsOnly, Category = "Ultimate")
	bool bUltimateWithTick;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
	bool bCanUseUltimate;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
	bool bIsUsingUltimate;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	FName MeleeSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	TArray<FName> DoorKeys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AEM_Weapon> InitialWeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EEM_CharacterType CharacterType;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	AEM_Weapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* MeleeMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* UltimateMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Status Effects")
	UParticleSystem* PoisonEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Status Effects")
	UParticleSystem* UltimateEffect;

	UAnimInstance* MyAnimInstance;

	FTimerDelegate FakeWallTimerDel;

	FTimerHandle FakeWallDestroyTimer;

	FTimerHandle StatusEffectTimer;

	FTimerHandle StatusEffectDPSTimer;

	FTimerHandle UltimateTimer;

	FTimerHandle BeginUltimateBehaviorTimer;

	AEM_GameMode* GameModeReference;

	AEM_Dummy* DummyActor;

	TArray<AActor*> DummiesList;

public:
	// Sets default values for this character's properties
	AEM_Character();

	virtual FVector GetPawnViewLocation() const override;

	AEM_LaunchPad* CurrentLaunchPad;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitializeReferences();

	void MoveForward(float value);

	void MoveRight(float value);

	virtual void Jump() override;

	virtual void StopJumping() override;

	void StartCrouch();

	virtual void Crouch(bool bClientSimulation) override;

	virtual void UnCrouch(bool bClientSimulation) override;

	void CreateInitialWeapon();

	void StartWeaponAction();

	void StopWeaponAction();

	void StartMelee();

	void StopMelee();

	void DestroyFakeWall(AActor* DestructibleActor);

	void RemovePoisonStatusEffect();

	void MakeDamagePerSecond();

	void StartUltimate();

	void StopUltimate();

	UFUNCTION()
	void MakeMeleeDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHealthChange(UEM_HealthComponent* MyHealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AddControllerPitchInput(float value) override;

	void AddKey(FName NewKey);

	bool HasKey(FName KeyTag);

	void ActivateLaunchPad();

	void SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState);

	void SetMeleeState(bool NewState);

	void SetPoisonStatusEffect();

	UFUNCTION(BlueprintCallable)
	void SetComboEnabled(bool NewState);

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	bool HasToDestroy() { return bHasToDestroy; };

	UFUNCTION(BlueprintCallable)
	void GainUltimateXP(float XPGained);

	void UpdateUltimateDuration(float Value);

	void UpdateUltimateDurationWithTimer();

	void BeginUltimateBehavior();

	void StartStunEffect();

	void StopStunEffect();

	UFUNCTION(BlueprintCallable)
	EEM_CharacterType GetCharacterType() { return CharacterType; };

protected:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GainUltimateXP(float XPGained);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_StartUltimate();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_UpdateUltimateDuration(float Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_StopUltimate();
};
