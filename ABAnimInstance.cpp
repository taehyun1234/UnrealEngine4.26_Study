// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	_currentPawnSpeed = 0.f;
	_isInAir = false;
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