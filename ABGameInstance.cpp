// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	FString characterDataPath = TEXT("/Game/Book/GameData/ABCharacterData.ABCharacterData");
	// csv파일의 경로를 받아온다.
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_abCharacter(*characterDataPath);
	// objectFind를 이용해 datapath를 찾아서 초기화한다. -> FObjectFinder에 대해 알아볼 것.
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
	// level에 해당하는 행을 읽어서 리턴한다.
}
