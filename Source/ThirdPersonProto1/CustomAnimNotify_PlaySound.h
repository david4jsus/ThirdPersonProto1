// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CustomAnimNotify_PlaySound.generated.h"

// Forward declarations
class USoundBase;

/**
 * 
 */
UCLASS()
class THIRDPERSONPROTO1_API UCustomAnimNotify_PlaySound : public UAnimNotify
{
	GENERATED_BODY()

public:

	 // The sound to play when this anim notif is reached
	 UPROPERTY(EditAnywhere, Category = "Sound")
	 USoundBase* sound;

	 // Whether the sound should have variation
	 UPROPERTY(EditAnywhere, Category = "Sound")
	 bool SoundVariation;

	 // Whether the sound should cut itself when already playing (or wait until playback finished)
	 UPROPERTY(EditAnywhere, Category = "Sound")
	 bool CutItself;

public:

	 // Constructor
	 UCustomAnimNotify_PlaySound();

	 // Fire events when notify occurs
	 virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
