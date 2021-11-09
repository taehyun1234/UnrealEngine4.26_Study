// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	_currentPawnSpeed = 0.f;
	_isInAir = false;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> attackMontage(
		TEXT("/Game/Book/Animations/WarriorAttack.WarriorAttack"));

	if (attackMontage.Succeeded())
	{
		_attackMontage = attackMontage.Object;
	}

}

void UABAnimInstance::NativeUpdateAnimation(float deltaSeconds)
{
	Super::NativeUpdateAnimation(deltaSeconds);

	auto pawn = TryGetPawnOwner();
	if (::IsValid(pawn))
	{
		_currentPawnSpeed = pawn->GetVelocity().Size();

		auto character = Cast<ACharacter>(pawn);
		if (character)
		{
			_isInAir = character->GetMovementComponent()->IsFalling();
		}
	}
}

void UABAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(_attackMontage))
	{
		Montage_Play(_attackMontage,1.0f);
	}
}

void UABAnimInstance::AnimNotify_AttackHitCheck()
{
	onAttackHitCheck.Broadcast();
}

void UABAnimInstance::AnimNotify_NextAttackCheck()
{
	onNextAttackCheck.Broadcast();
}

void UABAnimInstance::JumpToAttackMontageSection(int32 newSection)
{
	ABCHECK(Montage_IsPlaying(_attackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(newSection), _attackMontage);
}

FName UABAnimInstance::GetAttackMontageSectionName(int32 section)
{
	ABCHECK(FMath::IsWithinInclusive<int32>(section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), section));
}
