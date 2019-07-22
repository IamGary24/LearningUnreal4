// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LearningMoreStuffPlayerController.h"
#include "GunProjectile.h"
#include "CreatureCreatedByPlayer.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "LearningMoreStuffCharacter.h"
#include "Engine/World.h"

ALearningMoreStuffPlayerController::ALearningMoreStuffPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ALearningMoreStuffPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ALearningMoreStuffPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ALearningMoreStuffPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ALearningMoreStuffPlayerController::OnSetDestinationReleased);

  // gfowler - bind the on shoot function
  InputComponent->BindAction("Shoot", IE_Pressed, this, &ALearningMoreStuffPlayerController::Shoot);

  // gfowler - bind the spawn creature function
  InputComponent->BindAction("Spawn", IE_Pressed, this, &ALearningMoreStuffPlayerController::Spawn);
}

void ALearningMoreStuffPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);

    // gfowler - Move the impact point a little so the creature does not step on the player, but will go to the same general location
    Hit.ImpactPoint.X += 50;
    Hit.ImpactPoint.Y += 50;
    Hit.ImpactPoint.Z += 50;

    // gfowler - Now move the creature with the new impact point
    ALearningMoreStuffCharacter* PlayableCharacter = Cast<ALearningMoreStuffCharacter>(GetPawn());
      if (PlayableCharacter->Creature)
      { 
        PlayableCharacter->Creature.SetNewCreatureDestination(Hit.ImpactPoint);
      }

	}
}


void ALearningMoreStuffPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ALearningMoreStuffPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ALearningMoreStuffPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ALearningMoreStuffPlayerController::Shoot()
{
  // Create a playable character object to spawn our projectile
  ALearningMoreStuffCharacter* PlayableCharacter = Cast<ALearningMoreStuffCharacter>(GetPawn());
  if (PlayableCharacter)
  {
    if (PlayableCharacter->Projectile)
    {
      // get where the character is so we can find where our projectile originates from
      FVector MuzzleLocation = PlayableCharacter->GetActorLocation();
      FRotator MuzzleRotation = PlayableCharacter->GetActorRotation();
      UWorld* World = GetWorld();
      if (World)
      {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = Instigator;
        // Spawn the projectile at the muzzle
        AGunProjectile* Projectile = World->SpawnActor<AGunProjectile>(PlayableCharacter->Projectile, MuzzleLocation, MuzzleRotation, SpawnParams);
        if (Projectile)
        {
          // fire in the direction our character is facing
          Projectile->FireInDirection(PlayableCharacter->GetActorForwardVector());
        }
      }
    }
  }
}

void ALearningMoreStuffPlayerController::Spawn()
{
  // Attempt to spawn a creature
  ALearningMoreStuffCharacter* PlayableCharacter = Cast<ALearningMoreStuffCharacter>(GetPawn());
  if (PlayableCharacter->Creature)
  {
    FVector CreatureSpawnLocation = PlayableCharacter->GetActorLocation();
    FRotator CreatureSpawnRotation = PlayableCharacter->GetActorRotation();

    // Move the spawn location to be slightly off
    CreatureSpawnLocation.X += 100.0f;
    CreatureSpawnLocation.Y += 100.0f;

    UWorld* World = GetWorld();
    if (World)
    {
      FActorSpawnParameters SpawnParams;
      SpawnParams.Owner = this;
      SpawnParams.Instigator = Instigator;
      //Spawn the pawn next to the player
      ACreatureCreatedByPlayer* Creature = World->SpawnActor<ACreatureCreatedByPlayer>(PlayableCharacter->Creature, CreatureSpawnLocation, CreatureSpawnRotation);
    }
  }
}
