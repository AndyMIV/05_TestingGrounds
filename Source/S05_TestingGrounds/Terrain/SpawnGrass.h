// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "SpawnGrass.generated.h"

/**
 * Code made by me
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class S05_TESTINGGROUNDS_API USpawnGrass : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

	USpawnGrass();
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SpawnTheGrass(int SpawnCount = 10);
	
	
};
