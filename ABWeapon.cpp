// Fill out your copyright notice in the Description page of Project Settings.


#include "ABWeapon.h"

// Sets default values
AABWeapon::AABWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	RootComponent = _weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> weapon(
		TEXT("/Game/Weapon_Pack/Skeletal_Mesh/SK_Sword.SK_Sword"));

	if (weapon.Succeeded())
	{
		_weapon->SetSkeletalMesh(weapon.Object);
	}
	_weapon->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AABWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

