// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "ABGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FABCharacterData : public FTableRowBase
{
	GENERATED_BODY()
public:
	FABCharacterData() : Level(1), MaxHP(100.f), Attack(10.f), DropExp(10), NextExp(30)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;		// ������ �� : csv���Ͽ� �ִ� ����� �̸��� ���� ������ �̸��� ��ġ�ؾ���. �׷��� ���� ��� �ν� x

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};


UCLASS()
class UNREALSTUDY_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

public:
	UABGameInstance();

	virtual void Init() override;
	FABCharacterData* GetABCharacterData(int32 level);

	FStreamableManager _streamableManager;
private:
	UPROPERTY()
	class UDataTable* _abCharacterTable;
};
