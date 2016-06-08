// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AIPatrolController.generated.h"

/**
 * 
 */
UCLASS()
class STEALTH_API AAIPatrolController : public AAIController
{
	GENERATED_BODY()

	/* Our blackboard component */
	UBlackboardComponent* BlackboardComp;

	/* our Behavior tree component */
	UBehaviorTreeComponent* BehaviorComp;

	/* Blackboard Keys */
	UPROPERTY(EditAnywhere, Category = "AI")
	FName LocationToGoKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	FName PlayerKey;

	TArray<AActor*> PatrolPoints;

	virtual void Possess(APawn* Pawn) override;


public:

	AAIPatrolController();

	void SetPlayerCaught(APawn* Pawn);

	/* Inline getter functions */
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }

	/* Players Current Patrol Point */
	int32 CurrentPatrolPoint;
};
