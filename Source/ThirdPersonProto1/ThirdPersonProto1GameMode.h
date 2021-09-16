// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ObjectiveSystem.h"
#include "ThirdPersonProto1GameMode.generated.h"

UCLASS(minimalapi)
class AThirdPersonProto1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	 // Objective system
	 ObjectiveSystem objectiveSystem = ObjectiveSystem(GetWorld());

public:
	AThirdPersonProto1GameMode();

	 /** Transitions to calls BeginPlay on actors. */
	 virtual void StartPlay() override;
};
