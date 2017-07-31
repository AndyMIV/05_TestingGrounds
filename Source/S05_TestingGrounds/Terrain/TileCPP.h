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

// BlueprintType not necesarilly needed. just split the pin in BP
USTRUCT(BlueprintType)
struct FInputVariables {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		int MinSpawn = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		int MaxSpawn = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		float Radius = 500;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		float MaxScale = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
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
		void PlaceActors(TSubclassOf<AActor> ToSpawn, FInputVariables InputVariables);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceAI(TSubclassOf<APawn> ToSpawn, FInputVariables InputVariables);


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

	void PositionNavMeshBoundsVolume();

	TArray<FSpawnPosition> GenerateSpawnPositions(FInputVariables InputVariables);

	UActorPool* Pool;

	AActor* NavMeshBoundsVolume = nullptr;




	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, FInputVariables InputVariables);

	void PlaceTheActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition PositionActor);

	void PlaceTheActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition PositionActor);
	

	
	
};
