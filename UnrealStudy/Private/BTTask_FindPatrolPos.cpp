// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"
#include "ABAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto controllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	// ������ Pawn�� null�� ��� ���� ����
	if (controllingPawn == nullptr)
		return EBTNodeResult::Failed;
	
	UNavigationSystemV1* navSystem = 
		UNavigationSystemV1::GetNavigationSystem(controllingPawn->GetWorld());

	// �׺���̼� System�� Null�� ��� ����
	if(navSystem == nullptr)
		return EBTNodeResult::Failed;

	// home��ġ�� origin���� �ʱ�ȭ
	FVector origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AABAIController::_homePosKey);
	FNavLocation nextPatrol;

	// NavSystem�� ���� ����Ʈ�� �� �����ε�, ������ ���, blackboard�� patrol position�� nextpatrol�� ��ġ�� �ٲ۴�.
	if (navSystem->GetRandomPointInNavigableRadius(origin, 500.f, nextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AABAIController::_patrolPosKey, nextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
