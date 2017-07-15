// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "PatrolRoute.h"


// Called every frame
TArray<AActor*> UPatrolRoute::GetPatrolPoints() const {
	return PatrolPointActors;
}

