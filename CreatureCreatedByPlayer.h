/*
This is the creature that is spawned by the player during gameplay.
Will handle creature AI and movement.
*/

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "CreatureCreatedByPlayer.generated.h"

UCLASS()
class LEARNINGMORESTUFF_API ACreatureCreatedByPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACreatureCreatedByPlayer();

  // Capsule collision component
  UPROPERTY(VisibleDefaultsOnly, Category = Creature)
  UCapsuleComponent* CollisionComponent;

  UPROPERTY(EditDefaultsOnly, Category = Creature)
  int CreatureCapsuleRadius;

  UPROPERTY(EditDefaultsOnly, Category = Creature)
  int CreatureCapsuleHeight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  /* Movement controller that will handle the creature's movement.

  The creature should move with the player, so when the player pawn gets a move command
  the creature will move as well in the same direction.
  The creature will always remain away from the player, and float around to make sure they
  do not hinder the path.

  @FVector Destination - will tell the creature where to go
  */
  void SetNewCreatureDestination(FVector Destination);

};
