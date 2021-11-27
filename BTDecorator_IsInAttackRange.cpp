// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "ABAIController.h"
#include "ABCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, nodeMemory);

	auto controllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (controllingPawn == nullptr) return false;

	auto target = Cast<AABCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AABAIController::_targetkey));

	if (target == nullptr)
		return false;

	bResult = (target->GetDistanceTo(controllingPawn) <= 200.f);
	
	return bResult;
}
