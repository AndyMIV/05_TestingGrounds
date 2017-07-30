// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "S05_TestingGroundsGameMode.h"
#include "TestingGroundsGameModeCPP.generated.h"

/**
 * 
 */
UCLASS()
class S05_TESTINGGROUNDS_API ATestingGroundsGameModeCPP : public AS05_TestingGroundsGameMode
{
	GENERATED_BODY()
	
	
public:
	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PopulateBoundsVolumePool();
	
};
