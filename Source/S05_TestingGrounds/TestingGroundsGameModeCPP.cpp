// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"  // needed for AActorIterator
#include "TestingGroundsGameModeCPP.h"


void ATestingGroundsGameModeCPP::PopulateBoundsVolumePool() {

	// responsible for 1 by 1 pointing at the different actors in the world (one at a time). In BP, use GetActorOfType
	// for less worsiness, you can use: auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	// trnslates to: if there is another actor iterator, then we can use this (ActorIterator has overloaded bool)
	while (VolumeIterator) {
		// ActorIterator has overloaded the * operator. * is the content of the ActorIterator, and the content is a actor pointer
		ANavMeshBoundsVolume* FoundActor = *VolumeIterator;
		UE_LOG(LogTemp, Warning, TEXT("Found Actor in PopulateBoundsVolumePool: %s"), *FoundActor->GetName());
		AddToPool(*VolumeIterator);
		++VolumeIterator; // moves to thge next actor.
	}

}


void ATestingGroundsGameModeCPP::AddToPool(ANavMeshBoundsVolume *VolumeToAdd) {
	UE_LOG(LogTemp, Warning, TEXT("Found Actor in AddToPool: %s"), *VolumeToAdd->GetName());
}

