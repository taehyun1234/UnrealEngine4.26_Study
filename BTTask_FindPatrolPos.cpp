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

	// 조종할 Pawn이 null일 경우 실패 리턴
	if (controllingPawn == nullptr)
		return EBTNodeResult::Failed;
	
	UNavigationSystemV1* navSystem = 
		UNavigationSystemV1::GetNavigationSystem(controllingPawn->GetWorld());

	// 네비게이션 System이 Null일 경우 실패
	if(navSystem == nullptr)
		return EBTNodeResult::Failed;

	// home위치를 origin으로 초기화
	FVector origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AABAIController::_homePosKey);
	FNavLocation nextPatrol;

	// NavSystem의 랜덤 포인트로 갈 예정인데, 성공할 경우, blackboard의 patrol position을 nextpatrol의 위치로 바꾼다.
	if (navSystem->GetRandomPointInNavigableRadius(origin, 500.f, nextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AABAIController::_patrolPosKey, nextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
