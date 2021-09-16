// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAnimNotify_PlaySound.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

UCustomAnimNotify_PlaySound::UCustomAnimNotify_PlaySound() : Super()
{
    // Initialize sound properties
    SoundVariation = true;
    CutItself = false;
}

void UCustomAnimNotify_PlaySound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    // Check that we can play the sound
    if (sound && MeshComp) {

        // Check that the sound is not infinitely looping
        if (!sound->IsLooping()) {

            // Calculate pitch multiplier (in case we want variation)
            float pitchMultiplier = 1.0f;
            if (SoundVariation) {
                pitchMultiplier = FMath::RandRange(1.0f, 1.3f);
            }

            // Play the sound
            UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), sound, MeshComp->GetComponentLocation(), 1.0f, pitchMultiplier);
        }
    }
}
