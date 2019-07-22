// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "GunProjectile.h"
#include "Engine/World.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to NOT call Tick() every frame.
	PrimaryActorTick.bCanEverTick = false;

  // gfowler - root component will be a box
  CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
  // Set the root component to be the collision component
  RootComponent = CollisionComponent;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
  // every two seconds after the enemy is spawned they will fire a projectile
  UWorld* World = GetWorld();
  if (World)
  {
    World->GetTimerManager().SetTimer(ShootingTimerHandler, this, &AEnemy::Shoot, 1.0f, true, 2.0f);
  }
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::Shoot()
{
  if (ProjectileClass)
  {
    // get where the pawn is so we can find where our projectile originates from
    FVector MuzzleLocation = GetActorLocation();
    FRotator MuzzleRotation = GetActorRotation();
    UWorld* World = GetWorld();
    if (World)
    {
      FActorSpawnParameters SpawnParams;
      SpawnParams.Owner = this;
      SpawnParams.Instigator = Instigator;

      // Spawn the projectile at the muzzle
      AGunProjectile* Projectile = World->SpawnActor<AGunProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
      if (Projectile)
      {
        // fire in the direction our character is facing
        Projectile->FireInDirection(GetActorForwardVector());
      }
    }
  }
}

