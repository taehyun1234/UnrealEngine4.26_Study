// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "ABAIController.h"
#include "ABCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"


UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.f;		// 이 주기를 간격으로 TickNode를 호출함.
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto controllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (controllingPawn == nullptr)
		return;

	UWorld* world = controllingPawn->GetWorld();
	FVector center = controllingPawn->GetActorLocation();
	float detectRad = 600.f;

	// world가 없을 경우 리턴한다. -> 캐릭터의 월드좌표가 없다는건 말이안댐
	if (world == nullptr) return;

	TArray<FOverlapResult> overlapResults;
	FCollisionQueryParams collisionQueryParam(NAME_None, false, controllingPawn);
	bool bResult = world->OverlapMultiByChannel(
		overlapResults,
		center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(detectRad),
		collisionQueryParam
	);

	if (bResult)
	{
		for (auto overlapResult : overlapResults)
		{
			AABCharacter* abCharacter = Cast<AABCharacter>(overlapResult.GetActor());
			if (abCharacter && abCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AABAIController::_targetkey, abCharacter);
				DrawDebugSphere(world, center, detectRad, 16, FColor::Green, false, 0.2f);

				DrawDebugPoint(world, abCharacter->GetActorLocation(), 10.f, FColor::Blue, false, 0.2f);
				DrawDebugLine(world, controllingPawn->GetActorLocation(),abCharacter->GetActorLocation(), FColor::Blue, false, 0.27f);
				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AABAIController::_targetkey, nullptr);
	}
	DrawDebugSphere(world, center, detectRad, 16, FColor::Red, false, 0.2f);
}
