// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EMovementUpgrade.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EMovementUpgrade : uint8 {
    MU_NULL        UMETA(DisplayName = "Empty (No upgrade)"),
    MU_DOUBLE_JUMP UMETA(DisplayName = "Double Jump"),
    MU_TRIPLE_JUMP UMETA(DisplayName = "Triple Jump"),
    MU_SPRINT      UMETA(DisplayName = "Sprint"),
    MU_DASH        UMETA(DisplayName = "Dash"),
    MU_HOOK        UMETA(DisplayName = "Hook")
};

/*class THIRDPERSONPROTO1_API EMovementUpgrade
{
public:
	EMovementUpgrade();
	~EMovementUpgrade();
};*/