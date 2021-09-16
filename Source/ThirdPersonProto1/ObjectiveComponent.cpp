// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveComponent.h"
#include "ThirdPersonProto1GameMode.h"

// Sets default values for this component's properties
UObjectiveComponent::UObjectiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UObjectiveComponent::ProgressCurrentObjective()
{
	 // Get our custom game mode
	 AThirdPersonProto1GameMode* gamemode = Cast<AThirdPersonProto1GameMode>(GetWorld()->GetAuthGameMode());
	 if (!gamemode) {
		  return;
	 }

	 // Attempt to progress to the next objective
	 gamemode->objectiveSystem.ProgressToNextObjective();
}

void UObjectiveComponent::ProgressObjectiveByName()
{
	 // Get our custom game mode
	 AThirdPersonProto1GameMode* gamemode = Cast<AThirdPersonProto1GameMode>(GetWorld()->GetAuthGameMode());
	 if (!gamemode) {
		  return;
	 }

	 // Attempt to progress to the next objective with our specified objective name
	 gamemode->objectiveSystem.ProgressToNextObjectiveIfNameIs(objectiveName);
}

bool UObjectiveComponent::IsObjectiveComplete(FName objectiveToCheck)
{
	 // Get our custom game mode
	 AThirdPersonProto1GameMode* gamemode = Cast<AThirdPersonProto1GameMode>(GetWorld()->GetAuthGameMode());
	 if (!gamemode) return false;

	 // Check the progress of the specified objective
	 return gamemode->objectiveSystem.IsObjectiveComplete(objectiveToCheck);
}

// Called when the game starts
void UObjectiveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
/*void UObjectiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}*/

