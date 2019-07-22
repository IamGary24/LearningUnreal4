// Fill out your copyright notice in the Description page of Project Settings.


#include "GunProjectile.h"

// Sets default values
AGunProjectile::AGunProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Die after 3 seconds
  InitialLifeSpan = ProjectileLifeSpan;

  // Use a sphere as a simple collision representation
  CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
  // Set the collision radius
  CollisionComponent->InitSphereRadius(15.0f);
  // Set the root component to be the collision component
  RootComponent = CollisionComponent;

  // Component to drive projectile movement
  ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
  ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
  ProjectileMovementComponent->InitialSpeed = 500.0f;
  ProjectileMovementComponent->MaxSpeed = 500.0f;
  ProjectileMovementComponent->bRotationFollowsVelocity = true;
  ProjectileMovementComponent->bShouldBounce = true;
  ProjectileMovementComponent->Bounciness = 0.3f;
  ProjectileMovementComponent->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void AGunProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Initializes the projectile's velocity in the shoot direction.
void AGunProjectile::FireInDirection(const FVector& ShootDirection)
{
  ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

