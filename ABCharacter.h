// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ABWeapon.h"
#include "UnrealStudy.h"
#include "GameFramework/Character.h"
#include "ABCharacter.generated.h"

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
		DIABLO
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

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* _springArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* _camera;

private:
	void UpDown(float axisValue);
	void LeftRight(float axisValue);
	void Turn(float axisValue);
	void LookUp(float axisValue);

	void ViewChange();
	void Attack();

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
};
