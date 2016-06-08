// Fill out your copyright notice in the Description page of Project Settings.

#include "Stealth.h"
#include "AIPatrolController.h"
#include "AIPatrol.h"
#include "AIPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AAIPatrolController::AAIPatrolController()
{

	/* initialize blackboard and behavior tree */
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	/* initialize blackboard keys */
	LocationToGoKey = "LocationToGo";
	PlayerKey = "Target";
	
	CurrentPatrolPoint = 0;
}

void AAIPatrolController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	/* Get a reference to the possesed character */
	AAIPatrol* AICharacter = Cast<AAIPatrol>(Pawn);

	if (AICharacter)
	{
		/* If the blackboard is valid initialize the blackboard for the corresponding behavior tree */
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}

		/* Populate patrol points array */
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), PatrolPoints);

		/* Starts the behavior tree which coreresponds to the specific character */
		BehaviorComp->StartTree(*AICharacter->BehaviorTree);

	}
}

void AAIPatrolController::SetPlayerCaught(APawn* Pawn)
{	
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
	}
}
