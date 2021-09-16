// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveKey.h"

// Sets default values
AInteractiveKey::AInteractiveKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AInteractiveKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractiveKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveKey::Unlock(AInteractiveObstacle* obstacle)
{
	 // Perform only if the obstacle is active and locked
	 if (obstacle->GetObstacleActive() && obstacle->GetObstacleLocked()) {
		  obstacle->UnlockObstacle();
	 }
}

void AInteractiveKey::Lock(AInteractiveObstacle* obstacle)
{
	 // Perform only if the obstacle is active and unlocked
	 if (obstacle->GetObstacleActive() && !obstacle->GetObstacleLocked()) {
		  obstacle->LockObstacle();
	 }
}