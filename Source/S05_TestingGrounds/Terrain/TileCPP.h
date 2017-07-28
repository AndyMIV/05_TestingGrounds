// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TileCPP.generated.h"

UCLASS()
class S05_TESTINGGROUNDS_API ATileCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileCPP();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
