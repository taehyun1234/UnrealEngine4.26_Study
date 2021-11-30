// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "AIController.h"
#include "ABAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSTUDY_API AABAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AABAIController();
	virtual void OnPossess(APawn* inPawn) override;
	virtual void OnUnPossess() override;

	static const FName _homePosKey;
	static const FName _patrolPosKey;
	static const FName _targetkey;

private:
	UPROPERTY()
	class UBehaviorTree* _btAsset;

	UPROPERTY()
	class UBlackboardData* _bbAsset;		// 블랙보드는 행동트리에서 사용할 데이터 집합
};
