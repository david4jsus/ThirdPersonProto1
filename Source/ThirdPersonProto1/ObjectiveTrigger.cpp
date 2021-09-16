// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveTrigger.h"
#include "Components/BoxComponent.h"
#include "ObjectiveComponent.h"

// Sets default values
AObjectiveTrigger::AObjectiveTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set up trigger volume
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("ObjectiveTriggerVolume"));
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AObjectiveTrigger::EnterTriggerVolume);
	SetRootComponent(TriggerVolume);

	// Set up objective component
	objectiveComponent = CreateDefaultSubobject<UObjectiveComponent>(TEXT("ObjectiveTriggerObjectiveComponent"));
}

// Called every frame
/*void AObjectiveTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

void AObjectiveTrigger::EnterTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	 if (!objectiveComponent) return;
	 objectiveComponent->ProgressObjectiveByName();
}

// Called when the game starts or when spawned
void AObjectiveTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

