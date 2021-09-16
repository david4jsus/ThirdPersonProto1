// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonProto1GameMode.h"
#include "ThirdPersonProto1Character.h"
#include "UObject/ConstructorHelpers.h"

AThirdPersonProto1GameMode::AThirdPersonProto1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AThirdPersonProto1GameMode::StartPlay()
{
	 Super::StartPlay();

	 // Show the objective text in the HUD
	 objectiveSystem.UpdateAndShowObjectiveText();
}
