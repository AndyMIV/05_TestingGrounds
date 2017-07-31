// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TileCPP.generated.h"

USTRUCT()
struct FSpawnPosition {
	GENERATED_USTRUCT_BODY()


	FVector Location; 
	float Rotation; 
	float Scale;
};

USTRUCT()
struct FSpawnVariables {
	GENERATED_USTRUCT_BODY()

	int MinSpawn = 1;
	int MaxSpawn = 1;
	float Radius = 500;
	float MaxScale = 1;
	float MinScale = 1;


};

class UActorPool;

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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector MinBoxSize;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector MaxBoxSize;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
		FVector NavigationBoundsOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// setting up the reference for the pool class
	UFUNCTION(BlueprintCallable, Category = "Pool")
		void SetPool(UActorPool* Pool);

private:
	bool CastSphere(FVector Location, float Radius);
	bool FindEmptyLocation(FVector& OutLocation, float Radius);
	void PlaceTheActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition PositionActor);
	void PositionNavMeshBoundsVolume();
	TArray<FSpawnPosition> GenerateSpawnPositions(int MinSpawn, int MaxSpawn, float Radius, float MaxScale, float MinScale);

	UActorPool* Pool;
	AActor* NavMeshBoundsVolume = nullptr;
	

	
	
};
