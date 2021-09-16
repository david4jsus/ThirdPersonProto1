// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveSystem.h"
#include "InGameHUD.h"

ObjectiveSystem::ObjectiveSystem(UWorld* newWorld)
{
    // Get world reference
    world = newWorld;

    // Create some objectives
    Objective* objective1 = new Objective(0, FName("obj1"), FText::FromName(FName("Equip yourself")));
    Objective* objective2 = new Objective(1, FName("obj2"), FText::FromName(FName("Do a thing")));
    Objective* objective3 = new Objective(3, FName("obj3"), FText::FromName(FName("Get to the end")));
    objective1->SetNextObjective(objective2);
    objective2->SetNextObjective(objective3);

    // Add the objectives to the list of objectives
    objectiveList.Push(objective1);
    objectiveList.Push(objective2);
    objectiveList.Push(objective3);

    // Set the current objective
    currentObjective = objective1;

    // Show objective text
    //UpdateAndShowObjectiveText(); --> Best to do at a known safe time in the function call tree
}

ObjectiveSystem::~ObjectiveSystem()
{
    // Discard the objectives
    while (objectiveList.Num() > 0) {
        delete objectiveList.Pop();
    }
}

Objective* ObjectiveSystem::GetCurrentObjective()
{
    return currentObjective;
}

void ObjectiveSystem::ProgressToNextObjective()
{
    // Check that there is an objective selected
    if (currentObjective) {

        // Set current objective as complete
        currentObjective->SetComplete(true);

        // Proceed to next objective
        currentObjective = currentObjective->GetNextObjective();

        // Update objective text
        UpdateAndShowObjectiveText();
    }
}

void ObjectiveSystem::ProgressToNextObjectiveIfNameIs(FName objectiveName)
{
    // Check that there is an objective selected
    if (currentObjective) {

        // Check that the given name matches the name of the current objective
        if (currentObjective->GetName().Compare(objectiveName) == 0) {
            ProgressToNextObjective();
        }
    }
}

void ObjectiveSystem::UpdateAndShowObjectiveText()
{
    // Get instance of HUD
    AInGameHUD* InGameHUD = Cast<AInGameHUD>(world->GetFirstPlayerController()->GetHUD());

    // Check that the HUD instance was found
    if (!InGameHUD) {
        return;
    }

    // Check that there is an objective selected
    if (currentObjective) {

        // Interact with the HUD to show the objective text
        if (InGameHUD) {
            InGameHUD->UpdateAndShowObjectiveText(currentObjective->GetDescription().ToString());
        }
    }
    else {
        InGameHUD->HideObjectiveText();
    }
}

bool ObjectiveSystem::IsObjectiveComplete(FName objectiveName)
{
    // Get the objective with the given name
    Objective* objective = GetObjectiveByName(objectiveName);
    if (!objective) return false;

    // Get the objective's completion status
    return objective->IsComplete();
}

void ObjectiveSystem::SetCurrentObjective(Objective* newObjective)
{
    currentObjective = newObjective;
}

Objective* ObjectiveSystem::GetObjectiveByName(FName objectiveName)
{
    // Cycle through objectives in the list
    for (int i = 0; i < objectiveList.Num(); i++) {

        // Compare the given name with the current objective's name
        if (objectiveName.Compare(objectiveList[i]->GetName()) == 0) {

            // If the names match, return this objective
            return objectiveList[i];
        }
    }

    // If there are no matches, return null
    return nullptr;
}
