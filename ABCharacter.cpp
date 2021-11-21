// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"
#include "ABAnimInstance.h"
#include "DrawDebugHelpers.h"
// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f),
		FRotator(0.f, -90.f, 0.f));
	_springArm->TargetArmLength = 400.f;
	_springArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skCardBoard(
	TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (skCardBoard.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(skCardBoard.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> warriorAnim(
		TEXT("/Game/Book/Animations/WarriorAnimBluePrint.WarriorAnimBluePrint.WarriorAnimBlueprint_C"));
	if (warriorAnim.Succeeded())
	{
		GetMesh()->SetAnimClass(warriorAnim.Class);
	}

	_armLengthSpeed = 3.f;
	_armRotationSpeed = 10.f;
	GetCharacterMovement()->JumpZVelocity = 800.f;

	SetControlMode(_controlMode);

	_isAttacking = false;
	_maxCombo = 4;
	_curCombo = 0;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABCharacter"));

	_attackRange = 200.f;
	_attackRadius = 50.f;
}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABCharacter::SetControlMode(EControlMode controlMode)
{
	_controlMode = controlMode;

	switch (_controlMode)
	{
	case EControlMode::GTA:		
//		_springArm->TargetArmLength = 450.f;								// 카메라 지지대 길이
//		_springArm->SetRelativeRotation(FRotator::ZeroRotator);
		_armLengthTo = 450.f;
		_springArm->bUsePawnControlRotation = true;
		_springArm->bInheritPitch = true;
		_springArm->bInheritRoll = true;
		_springArm->bInheritYaw = true;
		_springArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
		break;
	case EControlMode::DIABLO:
//		_springArm->TargetArmLength = 800.f;								// 카메라 지지대 길이
//		_springArm->SetRelativeRotation(FRotator(-45.f,0.f,0.f));
		_armLengthTo = 800.f;
		_armRotationTo = FRotator(-45.f, 0.f, 0.f);
		_springArm->bUsePawnControlRotation = false;
		_springArm->bInheritPitch = false;
		_springArm->bInheritRoll = false;
		_springArm->bInheritYaw = false;
		_springArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
		break;
	}
}

// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_springArm->TargetArmLength = FMath::FInterpTo(_springArm->TargetArmLength,
		_armLengthTo, DeltaTime, _armLengthSpeed);

	switch (_controlMode)
	{
	case EControlMode::GTA:
		break;
	case EControlMode::DIABLO:
		_springArm->SetRelativeRotation(FMath::RInterpTo(_springArm->GetRelativeRotation(), 
			_armRotationTo, DeltaTime, _armRotationSpeed));
		break;
	}


	switch (_controlMode)
	{
	case EControlMode::GTA:
		break;
	case EControlMode::DIABLO:
		if (_directionToMove.SizeSquared() > 0.f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(_directionToMove).Rotator());
			AddMovementInput(_directionToMove);
		}
		break;
	}
}

// Called to bind functionality to input
void AABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AABCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AABCharacter::Turn);

	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &AABCharacter::ViewChange);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AABCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AABCharacter::Attack);
}

void AABCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_abAnim = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	ABCHECK(_abAnim != nullptr);

	_abAnim->OnMontageEnded.AddDynamic(this, &AABCharacter::OnAttackMontageEnded);

	_abAnim->onNextAttackCheck.AddLambda([this]() -> void
		{
			ABLOG(Warning, TEXT("OnNextAttackCheck"));
			_canNextCombo = false;

			if (_isComboinputOn)
			{
				AttackStartComboState();
				_abAnim->JumpToAttackMontageSection(_curCombo);
			}
		});
	_abAnim->onAttackHitCheck.AddUObject(this, &AABCharacter::AttackCheck);
}

float AABCharacter::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInvestigator, AActor* damageCauser)
{
	float finalDamage = Super::TakeDamage(damageAmount, damageEvent, eventInvestigator, damageCauser);
	ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), finalDamage);

	if (finalDamage > 0.f)
	{
		_abAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	}

	return finalDamage;
}

void AABCharacter::UpDown(float axisValue)
{
//	AddMovementInput(GetActorForwardVector(), axisValue);
	switch (_controlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), axisValue);
		break;
	case EControlMode::DIABLO:
		_directionToMove.X = axisValue;
		break;
	}
}

void AABCharacter::LeftRight(float axisValue)
{
//	AddMovementInput(GetActorRightVector(), axisValue);
	switch (_controlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), axisValue);
		break;
	case EControlMode::DIABLO:
		_directionToMove.Y = axisValue;
		break;
	}
}

void AABCharacter::Turn(float axisValue)
{
	switch (_controlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(axisValue);
		break;
	case EControlMode::DIABLO:
		break;
	}
}

void AABCharacter::LookUp(float axisValue)
{
	switch (_controlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(axisValue);
		break;
	case EControlMode::DIABLO:
		break;
	}
}

void AABCharacter::ViewChange()
{
	ABLOG(Warning, TEXT("ViewChange %f"),_springArm->TargetArmLength);
	switch (_controlMode)
	{
	case EControlMode::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);
		break;
	case EControlMode::DIABLO:
		GetController()->SetControlRotation(_springArm->GetRelativeRotation());
		SetControlMode(EControlMode::GTA);
		break;
	}
}

void AABCharacter::Attack()
{
	//if (_isAttacking)return;
	//auto animInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	//if (animInstance == nullptr) return;
	//
	//animInstance->PlayAttackMontage();
	//_isAttacking = true;
	ABLOG(Warning, TEXT("Attack"));

	if (_isAttacking)
	{
		ABLOG(Warning, TEXT("Attack1"));
		ABCHECK(FMath::IsWithinInclusive<int32>(_curCombo, 1, _maxCombo));
		if (_canNextCombo)
		{
			_isComboinputOn = true;
		}
	}
	else
	{
		ABCHECK(_curCombo == 0);
		AttackStartComboState();
		_abAnim->PlayAttackMontage();
		_abAnim->JumpToAttackMontageSection(_curCombo);
		_isAttacking = true;
	}
}


void AABCharacter::OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted)
{
	ABCHECK(_isAttacking);
	ABCHECK(_curCombo > 0);
	_isAttacking = false;
	AttackEndComboState();
}

void AABCharacter::AttackStartComboState()
{
	_canNextCombo = true;
	_isComboinputOn = false;
	ABCHECK(FMath::IsWithinInclusive<int32>(_curCombo, 0, _maxCombo - 1));
	_curCombo = FMath::Clamp<int32>(_curCombo + 1, 1, _maxCombo);
}

void AABCharacter::AttackEndComboState()
{
	_isComboinputOn = false;
	_canNextCombo = false;
	_curCombo = 0;
}

void AABCharacter::AttackCheck()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.f),
		params
	);
	
#if ENABLE_DRAW_DEBUG
	FVector traceVec = GetActorForwardVector() * _attackRange;
	FVector center = GetActorLocation() + traceVec * 0.5f;
	float halfHeight = _attackRange * 0.5f + _attackRadius;
	FQuat capsuleRot = FRotationMatrix::MakeFromZ(traceVec).ToQuat();
	FColor drawColor = bResult ? FColor::Green : FColor::Red;
	float debugLifeTime = 5.f;

	DrawDebugCapsule(GetWorld(),
		center,
		halfHeight,
		_attackRadius,
		capsuleRot,
		drawColor,
		false,
		debugLifeTime);
#endif
	if (bResult)
	{
		if (hitResult.Actor.IsValid())
		{
			ABLOG(Warning, TEXT("Hit Actor Name : %s"), *hitResult.Actor->GetName());

			FDamageEvent damageEvent;
			hitResult.Actor->TakeDamage(50.0f, damageEvent, GetController(), this);
			// TakeDamage 함수는 감지된 액터에게 데미지를 인가한다.
		}
	}

}

