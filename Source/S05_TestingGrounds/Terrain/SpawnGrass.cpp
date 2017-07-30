// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpawnGrass.h"

USpawnGrass::USpawnGrass() {
	SetCollisionProfileName(TEXT("NoCollision"));
}


void USpawnGrass::SpawnTheGrass(int SpawnCount) {
	auto Bounds = FBox(FVector(0.0, -2000.0, 0.0), FVector(4000.0, 2000.0, 0.0));
	for (int i = 0; i < SpawnCount; i++) {
		FVector Randomized = FMath::RandPointInBox(Bounds);
		FTransform URandomized = UKismetMathLibrary::Conv_VectorToTransform(Randomized);
		AddInstance(URandomized);
	}

}
