// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
};