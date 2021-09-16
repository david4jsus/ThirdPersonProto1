// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MovementUpgrade.h"
#include "CableComponent.h"
#include "HookPoint.h"
#include "Teleporter.h"
#include "ThirdPersonProto1Character.generated.h"

UCLASS(config=Game)
class AThirdPersonProto1Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AThirdPersonProto1Character();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// Handle crouching
	void ToggleCrouch();

	// Traces to find ledges
	bool ForwardTrace();
	bool HeightTrace();

	// Climb up on a ledge when hanging
	void ClimbUp();

	// Drop down form a ledge when hanging
	void DropDown();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	// Overlap function to interact with trigger volumes
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Overlap end function
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	// Stuff that happens when the character lands after falling
	virtual void Landed(const FHitResult& Hit) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Tick
	virtual void Tick(float DeltaTime) override;

	// Toggle the pause menu on or off
	UFUNCTION(BlueprintCallable, Category = "Pause Menu")
		 void TogglePauseMenu();

	// Open the pause menu
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pause Menu")
		 void OpenPauseMenu();
	void OpenPauseMenu_Implementation();

	// Close the pause menu
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pause Menu")
		 void ClosePauseMenu();
	void ClosePauseMenu_Implementation();

	// Interact with a newarby object
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		 void Interact();

	// Hanging animation montage
	UPROPERTY(EditAnywhere, Category="Animations")
		 UAnimMontage* hangingMontage;

	// Hanging property getter/setter
	UFUNCTION(BlueprintCallable)
		 void SetIsHanging(bool newIsHanging);
	UFUNCTION(BlueprintPure)
		 bool GetIsHanging();

	// Check whether hanging on a ledge is possible and do so
	UFUNCTION()
		 void StartHanging();

	// Transition out of hanging state (usually because ClimbUp())
	UFUNCTION()
		 void StopHanging();

	// Reset the hanging cooldown
	UFUNCTION()
		 void ResetHangingCooldown();

	// Start sprinting
	UFUNCTION()
		 void StartSprinting();

	// Stop sprinting
	UFUNCTION()
		 void StopSprinting();

	// Start dashing
	UFUNCTION()
		 void StartDashing();

	// Stop dashing
	UFUNCTION()
		 void StopDashing();

	// Reset dashing
	UFUNCTION()
		 void ResetDashing();

	// Toggle hook
	UFUNCTION()
		 void ToggleHook();

	// Start swinging
	UFUNCTION()
		 void StartSwinging();

	// Stop swinging
	UFUNCTION()
		 void StopSwinging();

	// Activate double jump upgrade
	UFUNCTION()
		 bool UpgradeToDoubleJump();

	// Activate triple jump upgrade
	UFUNCTION()
		 bool UpgradeToTripleJump();

	// Activate sprint upgrade
	UFUNCTION()
		 bool UpgradeToSprint();

	// Activate dash upgrade
	UFUNCTION()
		 bool UpgradeToDash();

	// Activate hook upgrade
	UFUNCTION()
		 bool UpgradeToHook();

	// Amount of lateral control while jumping/falling
	UPROPERTY(EditAnywhere, Category = "Character Movement: Air Control", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		 float airControl;

	// Max and min height of a ledge to allow hanging
	UPROPERTY(EditAnywhere, Category = "Character Movement: Hanging")
		 float minHangHeight;
	UPROPERTY(EditAnywhere, Category = "Character Movement: Hanging")
		 float maxHangHeight;

	// Cooldown before being able to hang to a ledge again
	UPROPERTY(EditAnywhere, Category = "Character Movement: Hanging")
		 float hangingCooldown;

	// Speed for sprinting
	UPROPERTY(EditAnywhere, Category = "Character Movement: Sprinting")
		 float sprintSpeed;

	// Dashing distance
	UPROPERTY(EditAnywhere, Category = "Character Movement: Dashing")
		 float dashDistance;

	// Speed to use when dashing stops
	UPROPERTY(EditAnywhere, Category = "Character Movement: Dashing")
		 float dashStopSpeed;

	// Time to dash for
	UPROPERTY(EditAnywhere, Category = "Character Movement: Dashing")
		 float dashingTime;

	// Dashing cooldown
	UPROPERTY(EditAnywhere, Category = "Character Movement: Dashing")
		 float dashingCooldown;

	// Hook cable
	UPROPERTY(VisibleAnywhere, Category = "Character Movement: Hook")
		 UCableComponent* hookCable;

	// Upgrade pickup sound
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
		 USoundBase* upgradePickupSound;

	// Dash sound
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
		 USoundBase* dashSound;

	// Hook sound
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
		 USoundBase* hookSound;

private:

	 // Keep track of whether the pause menu should be open or closed
	 bool bIsPauseMenuOpen;
	 
	 // Whether the character can currently interact
	 bool bCanInteract;

	 // Keep track of available movement upgrades if the player can interact with them (one at a time assumed)
	 EMovementUpgrade availableUpgrade;

	 // Keep track of upgrade actor to destroy it if upgrade is succesful
	 AMovementUpgrade* upgradeActor;

	 // Hanging/climbing ledges
	 FVector hangingWallLocation;
	 FVector hangingWallNormal;
	 FVector hangingWallHeight;
	 FTimerHandle hangingTimerHandle;
	 bool bCanHang;

	 // Sprinting
	 float nonSprintSpeed;

	 // Dashing
	 float defaultBreakingFrictionFactor;
	 FTimerHandle dashingTimerHandle;
	 bool bDidDash;

	 // Hook
	 AHookPoint* currentHookPointInRange;
	 AHookPoint* currentHookPointBeingUsed;

	 // Movement states
	 // bIsCrouched --> Already exists in ACharacter class
	 bool bIsHanging;
	 bool bIsClimbing;
	 bool bIsSprinting;
	 bool bIsDashing;
	 bool bIsSwinging;

	 // Movement upgrades
	 bool bIsDoubleJumpUpgrade;
	 bool bIsTripleJumpUpgrade;
	 bool bIsSprintUpgrade;
	 bool bIsDashUpgrade;
	 bool bIsHookUpgrade;

	 // Teleporting
	 ATeleporter* currentTeleporter;
	 bool bCanTeleport;
};