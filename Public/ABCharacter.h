// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "GameFramework/Character.h"
#include "ABCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class UNREALSTUDY_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

protected:
	// Called when the game starts or when spawned
	enum class EControlMode
	{
		GTA = 0,
		DIABLO,
		NPC
	};
	virtual void BeginPlay() override;

	void SetControlMode(EControlMode controlMode);

	EControlMode _controlMode = EControlMode::GTA;
	FVector _directionToMove = FVector::ZeroVector;

	float _armLengthTo = 0.f;
	FRotator _armRotationTo = FRotator::ZeroRotator;
	float _armLengthSpeed = 0.f;
	float _armRotationSpeed = 0.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, 
		AController* EventInstigator, AActor* DamageCauser) override;

	virtual void PossessedBy(AController* newController) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* _springArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* _camera;

	void Attack();
	FOnAttackEndDelegate OnAttackEnd;
private:
	void UpDown(float axisValue);
	void LeftRight(float axisValue);
	void Turn(float axisValue);
	void LookUp(float axisValue);

	void ViewChange();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool _isAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool _canNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool _isComboinputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 _curCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 _maxCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float _attackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float _attackRadius;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* _weapon;

	UPROPERTY()
	class UABAnimInstance* _abAnim;

public:
	bool CanSetWeapon();
	void SetWeapon(class AABWeapon* newWeapon);

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class AABWeapon* _currentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UABCharacterStatComponent* _characterStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* _hpBarWidget;
};
