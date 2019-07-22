/*
This player character class will hold all information for the character.
Created using the Top Down Coding Blueprint.
Changes are labeled with gfowler.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LearningMoreStuffCharacter.generated.h"

UCLASS(Blueprintable)
class ALearningMoreStuffCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALearningMoreStuffCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

  // gfowler - The projectile used to fire at enemies
  UPROPERTY(EditAnywhere, Category = "Stupid Category")
  TSubclassOf<class AGunProjectile> Projectile;

  // gfowler - The creature that we will spawn when cast
  UPROPERTY(EditAnywhere, Category = "Stupid Category")
  TSubclassOf<class ACreatureCreatedByPlayer> Creature;

  // gfowler - Gun muzzle's offset from camera location
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
  FVector MuzzleOffset = FVector(0, 0, 0);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};

