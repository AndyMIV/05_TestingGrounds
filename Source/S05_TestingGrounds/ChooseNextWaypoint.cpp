// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrollingGuard.h"  // think about removing
#include "AIController.h"
#include "ChooseNextWaypoint.h"



EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	// TODO protect against empty patrol routes
	// get the patrol points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto ControlledGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto ArrayOfActors = ControlledGuard->PatrolPointActorsCPP;

	// set next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName); // Experiment with strings
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, ArrayOfActors[Index]);

	// Cycle the index
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index + 1) % ArrayOfActors.Num());




	UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index);
	return EBTNodeResult::Succeeded;
}

