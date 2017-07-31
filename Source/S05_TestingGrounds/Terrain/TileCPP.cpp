// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "TileCPP.h"


// Sets default values
ATileCPP::ATileCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MinBoxSize = FVector(0.0, -2000.0, 0.0);
	MaxBoxSize = FVector(4000.0, 2000.0, 0.0);


}

void ATileCPP::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MaxScale, float MinScale) {

	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	UE_LOG(LogTemp, Warning, TEXT("I will spawn %i actors"), NumberToSpawn);

	for (int loop = 0; loop < NumberToSpawn; loop++) {
		FVector SpawnPoint;
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		Radius *= RandomScale;
			if (FindEmptyLocation(SpawnPoint, Radius)) {
				float RandomRotation = FMath::RandRange(-180.0f, 180.0f);
				PlaceTheActor(ToSpawn, SpawnPoint, RandomRotation, RandomScale);
		}

	//	FVector SpawnPoint = FMath::RandPointInBox(Bounds);
	//	UE_LOG(LogTemp, Warning, TEXT("Spawn point: %s"), *SpawnPoint.ToString());

			
			

	}

}

bool ATileCPP::FindEmptyLocation(FVector& SpawnPoint, float Radius) {
	// Min and max of fvector (magic numbers)
	auto Bounds = FBox(MinBoxSize, MaxBoxSize);

	int MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++) {
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (!CastSphere(CandidatePoint, Radius)) {
			SpawnPoint = CandidatePoint;
			return true;
		}
	}


	return false;
}


void ATileCPP::PlaceTheActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale) {
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	SpawnedActor->SetActorRelativeLocation(SpawnPoint);
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedActor->SetActorRotation(FRotator(0, Rotation, 0));
	SpawnedActor->SetActorScale3D(FVector(Scale));
}

// Called when the game starts or when spawned
void ATileCPP::BeginPlay()
{
	Super::BeginPlay();
	
	
}
void  ATileCPP::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	UE_LOG(LogTemp, Warning, TEXT("%s End play"), *GetName());
	Pool->Return(NavMeshBoundsVolume);
}

// Called every frame
void ATileCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATileCPP::CastSphere(FVector Location, float Radius) {

	FHitResult HitResult;

	// 
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);

	// we use channel so we can configuew what it hits later
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, 
		GlobalLocation, // was just Location, replaced to make positions global
		GlobalLocation,
		FQuat::Identity, 
		ECollisionChannel::ECC_GameTraceChannel2, // find & configure in system folder: config/DefaultEngine.ini
		FCollisionShape::MakeSphere(Radius));


	// ternary operator

	//FColor ResultColor = HasHit ? FColor::Red:FColor::Green;
	//	DrawDebugCapsule(     // can also use DrawDebugSphere (simpler code)
	//		GetWorld(),
	//		GlobalLocation,
	//		0,
	//		Radius,
	//		FQuat::Identity,
	//		ResultColor,
	//		true,
	//		100
	//	);

	return HasHit;
}

void ATileCPP::SetPool(UActorPool* InPool) {
	Pool = InPool;
	UE_LOG(LogTemp, Warning, TEXT("Setting pool %s"), *(InPool->GetName()));

	PositionNavMeshBoundsVolume();
}

void ATileCPP::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (NavMeshBoundsVolume == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not enough actors in pool!!!"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Checked out: %s"), *NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation());
}

