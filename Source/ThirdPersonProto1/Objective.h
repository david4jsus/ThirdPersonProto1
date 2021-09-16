// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class THIRDPERSONPROTO1_API Objective
{
public:
	Objective(int newID);
	Objective(int newID, FName newName, FText newDescription, Objective* newNextObjective = nullptr);
	~Objective();

	 // Get ID of this objective
	 UFUNCTION(BlueprintPure, Category = "Objective")
	 int GetID();

	 // Get the name of this objective
	 UFUNCTION(BlueprintPure, Category = "Objective")
	 FName GetName();

	 // Set the name of this objective
	 UFUNCTION(BlueprintCallable, Category = "Objective")
	 void SetName(FName newName);

	 // Get the description of this objective
	 UFUNCTION(BlueprintPure, Category = "Objective")
	 FText GetDescription();

	 // Set the description of this objective
	 UFUNCTION(BlueprintCallable, Category = "Objective")
	 void SetDescription(FText newDescription);

	 // Get whether this objective is complete
	 UFUNCTION(BlueprintPure, Category = "Objective")
	 bool IsComplete();

	 // Set whether this objective is complete
	 UFUNCTION(BlueprintCallable, Category = "Objective")
	 void SetComplete(bool completionStatus);

	 // Get the next objective
	 UFUNCTION(BlueprintPure, Category = "Objective")
	 Objective* GetNextObjective();

	 // Set the next objective
	 UFUNCTION(BlueprintCallable, Category = "Objective")
	 void SetNextObjective(Objective* newNextObjective);

private:

	 // Unique identifier for this objective
	 int id;

	 // Name of this objective
	 FName name;

	 // Description of this objective (text to give to the player regarding the objective)
	 FText description;

	 // Whether this objective is complete
	 bool bIsComplete;

	 // Pointer to another objective which will be followed once this one is complete
	 Objective* nextObjective;
};
