// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrollingGuard.h"  // think about removing
#include "PatrolRoute.h"
#include "AIController.h"
#include "ChooseNextWaypoint.h"



EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	// get the patrol route
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	// warn about empty patrol routes
	auto ArrayOfActors = PatrolRoute->GetPatrolPoints();
	if (ArrayOfActors.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("A Guard is missing patrol points"));
		return EBTNodeResult::Failed;
	}


	// set next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName); // Experiment with strings
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, ArrayOfActors[Index]);

	// Cycle the index
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index + 1) % ArrayOfActors.Num());

	UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index);
	return EBTNodeResult::Succeeded;
}

