// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	FString characterDataPath = TEXT("/Game/Book/GameData/ABCharacterData.ABCharacterData");
	// csv������ ��θ� �޾ƿ´�.
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_abCharacter(*characterDataPath);
	// objectFind�� �̿��� datapath�� ã�Ƽ� �ʱ�ȭ�Ѵ�. -> FObjectFinder�� ���� �˾ƺ� ��.
	ABCHECK(dt_abCharacter.Succeeded());
	_abCharacterTable = dt_abCharacter.Object;
	ABCHECK(_abCharacterTable->GetRowMap().Num() > 0);
}

void UABGameInstance::Init()
{
	Super::Init();
	int exp = GetABCharacterData(20)->DropExp;
	ABLOG(Warning, TEXT("DropExp of Level 20 abCharacter = %d"), exp);
}

FABCharacterData* UABGameInstance::GetABCharacterData(int32 level)
{
	return _abCharacterTable->FindRow<FABCharacterData>(*FString::FromInt(level), TEXT(""));
	// level�� �ش��ϴ� ���� �о �����Ѵ�.
}
