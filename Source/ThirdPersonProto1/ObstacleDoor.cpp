// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleDoor.h"

AObstacleDoor::AObstacleDoor()
{
    // Disable ticking
    PrimaryActorTick.bCanEverTick = false;

    // Set up the door mesh
    DoorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ObstacleDoorSkeletalMesh"));
    SetRootComponent(DoorMesh);
}

void AObstacleDoor::BeginPlay()
{
    Super::BeginPlay();

    // Set door mesh as open or closed based on initial variables
    if (GetObstacleLocked()) {
        CloseDoor();
    }
    else {
        OpenDoor();
    }
}

bool AObstacleDoor::LockObstacle()
{
    // Set lock variable
    Super::LockObstacle();

    // Close the door
    CloseDoor();

    // Successful locking
    return true;
}

bool AObstacleDoor::UnlockObstacle()
{
    // Set locking variable
    Super::UnlockObstacle();

    // Open the door
    OpenDoor();

    // Successful unlocking
    return true;
}

void AObstacleDoor::OpenDoor()
{
}

void AObstacleDoor::CloseDoor()
{
}
