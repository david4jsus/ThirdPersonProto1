// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyPressurePlate.h"

AKeyPressurePlate::AKeyPressurePlate()
{
    // Disable ticking
    PrimaryActorTick.bCanEverTick = false;

    // Setup pressure plate mesh
    PressurePlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyPressurePlateMesh"));
    SetRootComponent(PressurePlateMesh);

    // Setup trigger volume
    TriggerVolumeRadius = 100.0f;
    TriggerVolume = CreateDefaultSubobject<USphereComponent>(TEXT("KeyPressurePlateTriggerVolume"));
    TriggerVolume->SetSphereRadius(TriggerVolumeRadius);
    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AKeyPressurePlate::EnterTriggerVolume);
    TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AKeyPressurePlate::ExitTriggerVolume);
    TriggerVolume->SetupAttachment(GetRootComponent());
    TriggerVolume->SetRelativeLocation(FVector::UpVector * 110.0f);

    // Setup connected obstacle
    ConnectedObstacle = nullptr;

    // Setup objective component
    objectiveComponent = CreateDefaultSubobject<UObjectiveComponent>(TEXT("ObjectiveComponent"));
}

void AKeyPressurePlate::BeginPlay()
{
    Super::BeginPlay();
}

void AKeyPressurePlate::Unlock(AInteractiveObstacle* obstacle)
{
    // Perform only if the connected obstacle exists
    if (obstacle) {
        Super::Unlock(obstacle);

        // Attempt to progress objective system
        objectiveComponent->ProgressObjectiveByName();
    }
}

void AKeyPressurePlate::Lock(AInteractiveObstacle* obstacle)
{
    // Perform only if the connected obstacle exists
    if (obstacle) {
        Super::Lock(obstacle);
    }
}

void AKeyPressurePlate::EnterTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Unlock(ConnectedObstacle);
}

void AKeyPressurePlate::ExitTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    Lock(ConnectedObstacle);
}
