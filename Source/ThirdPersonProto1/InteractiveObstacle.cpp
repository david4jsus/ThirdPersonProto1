// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObstacle.h"

// Sets default values
AInteractiveObstacle::AInteractiveObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set activation properties
	StartActive = true;
	bIsActive = StartActive;

	// Set locking properties
	StartLocked = true;
	bIsLocked = StartLocked;

}

// Called when the game starts or when spawned
void AInteractiveObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractiveObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AInteractiveObstacle::GetObstacleActive() const
{
	 return bIsActive;
}

bool AInteractiveObstacle::ActivateObstacle()
{
	 // Activate obstacle
	 bIsActive = true;

	 // Successful activation
	 return true;
}

bool AInteractiveObstacle::DeactivateObstacle()
{
	 // Deactivate obstacle
	 bIsActive = false;

	 // Successful deactivation
	 return true;
}

bool AInteractiveObstacle::GetObstacleLocked() const
{
	 return bIsLocked;
}

bool AInteractiveObstacle::LockObstacle()
{
	 // Lock obstacle
	 bIsLocked = true;

	 // Successful locking
	 return true;
}

bool AInteractiveObstacle::UnlockObstacle()
{
	 // Unlock obstacle
	 bIsLocked = false;

	 // Successful unlocking
	 return true;
}

