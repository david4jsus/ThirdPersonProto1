// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObstacle.h"
#include "ObstacleDoor.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROTO1_API AObstacleDoor : public AInteractiveObstacle
{
	GENERATED_BODY()

public:

	 // Mesh of the door
	 UPROPERTY(VisibleAnywhere, Category = "Mesh")
	 USkeletalMeshComponent* DoorMesh;

protected:

private:

public:

	 // Sets default values for this actor's properties
	 AObstacleDoor();

protected:

	 // Called when the game starts or when spawned
	 virtual void BeginPlay() override;

	 // What to do when door locks
	 virtual bool LockObstacle() override;

	 // What to do when door unlocks
	 virtual bool UnlockObstacle() override;

private:

	 // Open door
	 void OpenDoor();

	 // Close door
	 void CloseDoor();
	
};
