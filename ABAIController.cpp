// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AABAIController::_homePosKey(TEXT("HomePos"));
const FName AABAIController::_patrolPosKey(TEXT("PatrolPos"));
const FName AABAIController::_targetkey(TEXT("Target"));
AABAIController::AABAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> 
		bbObject(TEXT("/Game/Book/AI/BB_ABCharacter.BB_ABCharacter"));

	if (bbObject.Succeeded())
	{
		_bbAsset = bbObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		btObject(TEXT("/Game/Book/AI/BT_ABCharacter.BT_ABCharacter"));

	if (btObject.Succeeded())
	{
		_btAsset = btObject.Object;
	}

}

void AABAIController::OnPossess(APawn* inPawn)
{ 
	Super::OnPossess(inPawn);
	if (UseBlackboard(_bbAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(_homePosKey, inPawn->GetActorLocation());
		if (!RunBehaviorTree(_btAsset))
		{
			ABLOG(Error, TEXT("AI Controller Couldn't run behavior tree"));
		}
	}
}

void AABAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
