// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "Character_PlayMontageNotify.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROTO1_API UCharacter_PlayMontageNotify : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()
	
public:

	 // Fire events when notify occurs
	 virtual void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;
};
