/*
The gunprojectile spawned when the player calls the shoot command
*/

#pragma once

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunProjectile.generated.h"

UCLASS()
class LEARNINGMORESTUFF_API AGunProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunProjectile();

  UPROPERTY(EditDefaultsOnly, Category = Projectile)
  int ProjectileLifeSpan = 3.0f;

  // Sphere collision component
  UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
  USphereComponent* CollisionComponent;

  // Projectile Movement component
  UPROPERTY(VisibleAnywhere, Category = Movement)
  UProjectileMovementComponent* ProjectileMovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
  // Initializes the projectile's velocity in the shoot direction
  void FireInDirection(const FVector& ShootDirection);
};
