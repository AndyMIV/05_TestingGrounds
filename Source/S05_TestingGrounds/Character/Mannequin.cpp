// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "../Weapons/Gun.h"
#include "Mannequin.h"


// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	MeshFP = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshFP"));
	MeshFP->SetOnlyOwnerSee(true);
	MeshFP->SetupAttachment(FirstPersonCameraComponent);
	MeshFP->bCastDynamicShadow = false;
	MeshFP->CastShadow = false;
	MeshFP->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	MeshFP->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();

	if (GunBlueprint == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Gun Blueprint Missing"));
		return;
	}

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	Gun = GetWorld()->SpawnActor<AGun>(
		GunBlueprint
		);

	Gun->AttachToComponent(MeshFP, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	// setting animation for gun - generally this should be made as a setter/getter if this will be used alot
	Gun->AnimInstance = MeshFP->GetAnimInstance();  // allows the gun to animate our mesh (such as kickback)
	
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannequin::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("I Fired"));
	Gun->OnFire();
}

