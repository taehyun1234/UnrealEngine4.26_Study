// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPawn.h"

// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	_movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));

	RootComponent = _capsule;
	_mesh->SetupAttachment(_capsule);
	_springArm->SetupAttachment(_capsule);
	_camera->SetupAttachment(_springArm);

	_capsule->SetCapsuleHalfHeight(88.f);
	_capsule->SetCapsuleRadius(34.f);
	_mesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f),
		FRotator(0.f, -90.f, 0.f));
	_springArm->TargetArmLength = 400.f;
	_springArm->SetRelativeLocation(FVector(-15.f, 0.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> sk_Cardboard(
		TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (sk_Cardboard.Succeeded())
	{
		_mesh->SetSkeletalMesh(sk_Cardboard.Object);
	}
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AABPawn::PossessedBy(AController* newCollider)
{
	ABLOG_S(Warning);
	Super::PossessedBy(newCollider);
}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABPawn::LeftRight);
}

void AABPawn::UpDown(float axisValue)
{
	ABLOG(Warning, TEXT("UpDown"));
	AddMovementInput(GetActorForwardVector(), axisValue);
}

void AABPawn::LeftRight(float axisValue)
{
	ABLOG(Warning, TEXT("LeftRight"));
	AddMovementInput(GetActorRightVector(), axisValue);
}

