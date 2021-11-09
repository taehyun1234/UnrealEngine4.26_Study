// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate)
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate)

/**
 * 
 */
UCLASS()
class UNREALSTUDY_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UABAnimInstance();
	virtual void NativeUpdateAnimation(float deltaSeconds) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn,
		Meta = (AllowPrivateAccess = true))
	float _currentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn,
		Meta = (AllowPrivateAccess = true))
	bool _isInAir;

public:
	void PlayAttackMontage();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* _attackMontage;

	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	void JumpToAttackMontageSection(int32 newSection);

public:
	FOnNextAttackCheckDelegate onNextAttackCheck;
	FOnAttackHitCheckDelegate onAttackHitCheck;

	FName GetAttackMontageSectionName(int32 section);
};
