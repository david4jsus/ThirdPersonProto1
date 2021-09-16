// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_PlayMontageNotify.h"
#include "ThirdPersonProto1Character.h"

// Fire events when notify occurs depending on notify name
void UCharacter_PlayMontageNotify::BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	 Super::BranchingPointNotify(BranchingPointPayload);

	 if (USkeletalMeshComponent* MeshComp = BranchingPointPayload.SkelMeshComponent)
	 {
		  if (UAnimInstance* AnimInstance = MeshComp->GetAnimInstance())
		  {
				// Get a reference to the character and verify we found it
				AThirdPersonProto1Character* character = Cast<AThirdPersonProto1Character>(MeshComp->GetOwner());
				if (character == NULL) {
					 return;
				}

				// Check for notify name and fire corresponding event
				if (NotifyName == FName(TEXT("StopHanging"))) {
					 character->StopHanging();
				}
		  }
	 }
}