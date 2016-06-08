// Fill out your copyright notice in the Description page of Project Settings.

#include "Stealth.h"
#include "BTSelectPatrolPoint.h"
#include "AIPatrolPoint.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAIPatrolController* AIController = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		/* Get Blackboard component */
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();

		AAIPatrolPoint* CurrentPoint = Cast<AAIPatrolPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailablePatrolPoints = AIController->GetPatrolPoints();

		AAIPatrolPoint* NextPatrolPoint = nullptr;

		if (AIController->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1)
		{
			/* Go to the next patrol point if not at the end*/
			NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[++AIController->CurrentPatrolPoint]);
		}
		else // if there are no more patrol points to go to
		{
			NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[0]);
			AIController->CurrentPatrolPoint = 0;
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
