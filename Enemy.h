/*
This is the enemy that is handplaced into the world. They will fire in a fixed direction.
*/

#pragma once

#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class LEARNINGMORESTUFF_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

  // will create a GunProjectile and shoot it at the player
  UFUNCTION()
  void Shoot();

  FTimerHandle ShootingTimerHandler;
  
  // Projectile class used to spawn the projectile being fired
  UPROPERTY(EditAnywhere, Category = "Stupid Category")
  TSubclassOf<class AGunProjectile> ProjectileClass;

  // Box collision component
  UPROPERTY(VisibleDefaultsOnly, Category = Creature)
  UBoxComponent* CollisionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
