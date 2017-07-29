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
		void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500, float MaxScale = 1, float MinScale = 1);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool CastSphere(FVector Location, float Radius);
	bool FindEmptyLocation(FVector& OutLocation, float Radius);
	void PlaceTheActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale);

	
	
};
