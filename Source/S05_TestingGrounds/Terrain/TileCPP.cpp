// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "TileCPP.h"


// Sets default values
ATileCPP::ATileCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATileCPP::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn) {
	// Min and max of fvector (magic numbers)
	auto Bounds = FBox(FVector(0.0, -2000.0, 0.0), FVector(4000.0, 2000.0, 0));
	FVector SpawnPoint = FMath::RandPointInBox(Bounds);

	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (int loop = 0; loop < NumberToSpawn; loop++) {
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		UE_LOG(LogTemp, Warning, TEXT("Spawn point: %s"), *SpawnPoint.ToString());
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);

		SpawnedActor->SetActorRelativeLocation(SpawnPoint);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));


			
			

	}

}

// Called when the game starts or when spawned
void ATileCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

