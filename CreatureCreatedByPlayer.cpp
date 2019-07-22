// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureCreatedByPlayer.h"

// Sets default values
ACreatureCreatedByPlayer::ACreatureCreatedByPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // gfowler - root component will be a capsule
  CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
  // Set the collision radius
  CollisionComponent->InitCapsuleSize(CreatureCapsuleRadius, CreatureCapsuleHeight);
  // Set the root component to be the collision component
  RootComponent = CollisionComponent;

}

// Called when the game starts or when spawned
void ACreatureCreatedByPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACreatureCreatedByPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACreatureCreatedByPlayer::SetNewCreatureDestination(FVector Destination)
{
  APawn* const MyPawn = GetPawn();
  if (MyPawn)
  {
    float const Distance = FVector::Dist(Destination, MyPawn->GetActorLocation());

    // We need to issue move command only if far enough in order for walk animation to play correctly
    if ((Distance > 120.0f))
    {
      UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
    }
  }
}


