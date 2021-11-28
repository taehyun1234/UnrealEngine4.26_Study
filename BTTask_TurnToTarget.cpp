// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "ABCharacter.h"
#include "ABAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto abCharacter = Cast<AABCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (abCharacter == nullptr)
		return EBTNodeResult::Failed;

	auto target = Cast<AABCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AABAIController::_targetkey));
	if (target == nullptr)
		return EBTNodeResult::Failed;

	FVector lookVector = target->GetActorLocation() - abCharacter->GetActorLocation();
	lookVector.Z = 0.f;
	FRotator targetRot = FRotationMatrix::MakeFromX(lookVector).Rotator();
	abCharacter->SetActorRotation(FMath::RInterpTo(abCharacter->GetActorRotation(), targetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;

}