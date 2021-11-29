// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacterStatComponent.h"
#include "ABGameInstance.h"

// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;				// 이 변수를 true로 바꾸면, 스탯에 변경이 있을 때 InitializeComponent함수를 호출함.

	// ...
	_level = 1;
}


// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UABCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(_level);
}

void UABCharacterStatComponent::SetNewLevel(int32 newLevel)
{
	auto abGameInstance = Cast<UABGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ABCHECK(abGameInstance != nullptr);
	_currentStatData = abGameInstance->GetABCharacterData(newLevel);
	if (_currentStatData != nullptr)
	{
		_level = newLevel;
		SetHP(_currentStatData->MaxHP);
	}
	else
	{
		ABLOG(Error, TEXT("Level %d data doesn't exist"), newLevel);
	}
}

void UABCharacterStatComponent::SetDamage(float newDamage)
{
	ABCHECK(_currentStatData != nullptr);
//	_currentHp = FMath::Clamp<float>(_currentHp - newDamage, 0.f, _currentStatData->MaxHP);
	SetHP(FMath::Clamp<float>(_currentHp - newDamage, 0.f, _currentStatData->MaxHP));
}

void UABCharacterStatComponent::SetHP(float newHP)
{
	_currentHp = newHP;
	onHpChanged.Broadcast();
	if (_currentHp <= 0.f)
	{
		_currentHp = 0.f;
		onHpisZero.Broadcast();
	}
}

float UABCharacterStatComponent::GetAttack()
{
	ABCHECK(_currentStatData != nullptr, 0.f);
	return _currentStatData->Attack;
}

float UABCharacterStatComponent::GetHPRatio()
{
	ABCHECK(_currentStatData != nullptr, 0.f);

	return (_currentStatData->MaxHP < KINDA_SMALL_NUMBER ? 0.f : (_currentHp / _currentStatData->MaxHP));
}


// Called every frame
void UABCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

