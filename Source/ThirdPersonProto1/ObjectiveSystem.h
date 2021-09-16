// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"

/**
 * 
 */
class THIRDPERSONPROTO1_API ObjectiveSystem
{
private:

	 // List of objectives
	 TArray<Objective*> objectiveList;

	 // Current objective
	 Objective* currentObjective;

	 // Reference to the world (to get the HUD instance in charge of the objective text)
	 UWorld* world;

public:
	 ObjectiveSystem(UWorld* newWorld);
	 ~ObjectiveSystem();
	 
	 // Get the current objective
	 UFUNCTION(BlueprintPure, Category = "Objective System")
	 Objective* GetCurrentObjective();

	 // Progress to the next objective
	 UFUNCTION(BlueprintCallable, Category = "Objective System")
	 void ProgressToNextObjective();

	 // Progress to the next objective only if the given objective name is matched to the current objective
	 UFUNCTION(BlueprintCallable, Category = "Objective System")
	 void ProgressToNextObjectiveIfNameIs(FName objectiveName);

	 // Update and show the objective text
	 UFUNCTION(BlueprintCallable, Category = "Objective System")
	 void UpdateAndShowObjectiveText();

	 // Check whether a specified objective is complete
	 UFUNCTION(BlueprintCallable, Category = "Objective System")
	 bool IsObjectiveComplete(FName objectiveName);

private:

	 // Set the current objective
	 UFUNCTION(BlueprintCallable, Category = "Objective System")
	 void SetCurrentObjective(Objective* newObjective);

	 // Search for an objective with the given name
	 UFUNCTION(BlueprintCallable, Category = "Objective System")
	 Objective* GetObjectiveByName(FName objectiveName);
};
