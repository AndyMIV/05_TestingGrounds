// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "TileCPP.h"

// There is a current problem in architecture. Because we are finding a collection of random locations and then spawning, it causes
// the FindEmptyLocations to not keep track of places that will be taken up, thus causing meshes to collide (but they still spawn in because
// of our faulty logic)

// the way to make templates
//template<class T>
//T GetMax(T a, T b) {
//	if (a > b) {
//		return a;
//	}
//	else {
//		return b;
//	}
//}

// Sets default values
ATileCPP::ATileCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MinBoxSize = FVector(0.0, -2000.0, 0.0);
	MaxBoxSize = FVector(4000.0, 2000.0, 0.0);

	NavigationBoundsOffset = FVector(2000, 0, 0);


}

void ATileCPP::PlaceActors(TSubclassOf<AActor> ToSpawn, FInputVariables InputVariables) {

	RandomlyPlaceActors(ToSpawn, InputVariables);


	// TArray <FSpawnPosition> ArrSpawnPosition = GenerateSpawnPositions(InputVariables);

	/*for (FSpawnPosition SpawnPosition : ArrSpawnPosition) {
		PlaceTheActor(ToSpawn, SpawnPosition);
		
	}*/




}

void ATileCPP::PlaceAI(TSubclassOf<APawn> ToSpawn, FInputVariables InputVariables) {
	RandomlyPlaceActors(ToSpawn, InputVariables);
	// TArray <FSpawnPosition> ArrSpawnPosition = GenerateSpawnPositions(InputVariables);

	/*for (FSpawnPosition SpawnPosition : ArrSpawnPosition) {
		PlaceTheAI(ToSpawn, SpawnPosition);

	}*/

}

// depreceated function (code has been extracted out)
TArray<FSpawnPosition> ATileCPP::GenerateSpawnPositions(FInputVariables InputVariables) {

	TArray <FSpawnPosition> ArrSpawnPosition;
	int NumberToSpawn = FMath::RandRange(InputVariables.MinSpawn, InputVariables.MaxSpawn);

	for (int loop = 0; loop < NumberToSpawn; loop++) 
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(InputVariables.MinScale, InputVariables.MaxScale);
		float NewRadius= SpawnPosition.Scale * InputVariables.Radius;

		if (FindEmptyLocation(SpawnPosition.Location, NewRadius))
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.0f, 180.0f);
			ArrSpawnPosition.Add(SpawnPosition);
		}

	}

	return ArrSpawnPosition;

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

template<class T>
void ATileCPP::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, FInputVariables InputVariables) {

	int NumberToSpawn = FMath::RandRange(InputVariables.MinSpawn, InputVariables.MaxSpawn);

	for (int loop = 0; loop < NumberToSpawn; loop++) 
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(InputVariables.MinScale, InputVariables.MaxScale);
		float NewRadius= SpawnPosition.Scale * InputVariables.Radius;

		if (FindEmptyLocation(SpawnPosition.Location, NewRadius))
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.0f, 180.0f);
			PlaceTheActor(ToSpawn, SpawnPosition);

		}

	}


}


void ATileCPP::PlaceTheActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition PositionActor) {
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	if (SpawnedActor) {
		SpawnedActor->SetActorRelativeLocation(PositionActor.Location);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		SpawnedActor->SetActorRotation(FRotator(0, PositionActor.Rotation, 0));
		SpawnedActor->SetActorScale3D(FVector(PositionActor.Scale));
	}
	
}

void ATileCPP::PlaceTheActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition PositionActor) {
	APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(ToSpawn);
	if (SpawnedPawn) {
		SpawnedPawn->SetActorRelativeLocation(PositionActor.Location + FVector(0, 0, 200));
		SpawnedPawn->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		SpawnedPawn->SetActorRotation(FRotator(0, PositionActor.Rotation, 0));
		SpawnedPawn->SpawnDefaultController();
		SpawnedPawn->Tags.Add(FName("Enemy"));
	}
	
}


/// depreceated fucntion
//void ATileCPP::PlaceTheAI(TSubclassOf<APawn> ToSpawn, FSpawnPosition PositionActor) {
//	APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(ToSpawn);
//
//	SpawnedPawn->SetActorRelativeLocation(PositionActor.Location + FVector(0, 0, 200));
//	SpawnedPawn->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
//	SpawnedPawn->SetActorRotation(FRotator(0, PositionActor.Rotation, 0));
//	SpawnedPawn->SpawnDefaultController();
//	SpawnedPawn->Tags.Add(FName("Enemy"));
//}

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
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);


	// update navigation system
	GetWorld()->GetNavigationSystem()->Build();
}

