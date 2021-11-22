// Fill out your copyright notice in the Description page of Project Settings.


#include "ABItemBox.h"
#include "ABWeapon.h"
#include "ABCharacter.h"

// Sets default values
AABItemBox::AABItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	_box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	_effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = _trigger;
	_box->SetupAttachment(RootComponent);
	_effect->SetupAttachment(RootComponent);

	_trigger->SetBoxExtent(FVector(40.f, 42.f, 30.f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> 
		smBox(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));

	if (smBox.Succeeded())
	{
		_box->SetStaticMesh(smBox.Object);
	}
	_box->SetRelativeLocation(FVector(0.f, -3.5f, -30.f));

	_trigger->SetCollisionProfileName(TEXT("ItemBox"));
	_box->SetCollisionProfileName(TEXT("NoCollision"));
	_weaponItemClass = AABWeapon::StaticClass();

	static ConstructorHelpers::FObjectFinder<UParticleSystem> pChestopen(
		TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));
	if (pChestopen.Succeeded())
	{
		_effect->SetTemplate(pChestopen.Object);
		_effect->bAutoActivate = false;
	}
}

// Called when the game starts or when spawned
void AABItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemBox::OnCharacterOverlap);
}

// Called every frame
void AABItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABItemBox::OnCharacterOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	ABLOG_S(Warning);

	auto abCharacter = Cast<AABCharacter>(otherActor);
	ABCHECK(abCharacter != nullptr);

	if (abCharacter != nullptr && _weaponItemClass != nullptr)
	{
		if (abCharacter->CanSetWeapon())
		{
			auto newWeapon = GetWorld()->SpawnActor<AABWeapon>(_weaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			abCharacter->SetWeapon(newWeapon);
			_effect->Activate(true);
			_box->SetHiddenInGame(true, true);
			SetActorEnableCollision(false);
			_effect->OnSystemFinished.AddDynamic(this, &AABItemBox::OnEffectFinished);
		}
		else
		{
			ABLOG(Warning, TEXT("%s can't equip weapon Currently"),*abCharacter->GetName());
		}
	}
}

void AABItemBox::OnEffectFinished(UParticleSystemComponent* pSystem)
{
	Destroy();
}

