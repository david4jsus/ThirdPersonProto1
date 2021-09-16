// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"

Objective::Objective(int newID)
{
    id = newID;
    bIsComplete = false;
    nextObjective = nullptr;
}

Objective::Objective(int newID, FName newName, FText newDescription, Objective* newNextObjective)
{
    id = newID;
    name = newName;
    description = newDescription;
    bIsComplete = false;
    nextObjective = newNextObjective;
}

Objective::~Objective()
{
}

int Objective::GetID()
{
    return id;
}

FName Objective::GetName()
{
    return name;
}

void Objective::SetName(FName newName)
{
    name = newName;
}

FText Objective::GetDescription()
{
    return description;
}

void Objective::SetDescription(FText newDescription)
{
    description = newDescription;
}

bool Objective::IsComplete()
{
    return bIsComplete;
}

void Objective::SetComplete(bool completionStatus)
{
    bIsComplete = completionStatus;
}

Objective* Objective::GetNextObjective()
{
    return nextObjective;
}

void Objective::SetNextObjective(Objective* newNextObjective)
{
    nextObjective = newNextObjective;
}
