// Fill out your copyright notice in the Description page of Project Settings.


#include "HookPoint.h"

// Sets default values
AHookPoint::AHookPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the static mesh component
	hookPointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HookPointMesh"));
	RootComponent = hookPointMesh;

	// Create the sphere volume componnet
	triggerVolumeRadius = 500.0f;
	triggerVolume = CreateDefaultSubobject<USphereComponent>(TEXT("HookPointTriggerVolume"));
	triggerVolume->SetSphereRadius(triggerVolumeRadius);
	// Can use overlap functions to trigger animation states
	triggerVolume->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AHookPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
/*void AHookPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/