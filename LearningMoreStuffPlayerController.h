/* 
This player controller handles movement of the player and abilities they have.
Created using the Top Down Coding Blueprint.
Changes are labeled with gfowler.
*/
#pragma once

#include "CoreMinimal.h"
#include "GunProjectile.h"
#include "GameFramework/PlayerController.h"
#include "LearningMoreStuffPlayerController.generated.h"

UCLASS()
class ALearningMoreStuffPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALearningMoreStuffPlayerController();

  // gfowler - Handles firing projectiles.
  UFUNCTION()
  void Shoot();

  // gfowler - spawn a creature pawn that follows its own AI, this will spawn next to the player
  UFUNCTION()
  void Spawn();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

};


