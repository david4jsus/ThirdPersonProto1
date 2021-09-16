// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonProto1Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// AThirdPersonProto1Character

AThirdPersonProto1Character::AThirdPersonProto1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	airControl = 0.75f;
	GetCharacterMovement()->AirControl = airControl;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Custom movement variables
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	hangingWallHeight = FVector();
	hangingWallLocation = FVector();
	hangingWallNormal = FVector();
	hangingCooldown = 1.0f;
	bCanHang = true;

	minHangHeight = 75.0f;
	maxHangHeight = 100.0f;

	nonSprintSpeed = GetCharacterMovement()->MaxWalkSpeed;
	sprintSpeed = 2000.0f;

	dashDistance = 8000.0f;
	dashStopSpeed = 500.0f;
	dashingTime = 0.1f;
	dashingCooldown = 0.75f;
	defaultBreakingFrictionFactor = GetCharacterMovement()->BrakingFrictionFactor;
	bDidDash = false;

	currentHookPointInRange = nullptr;
	currentHookPointBeingUsed = nullptr;
	hookCable = CreateDefaultSubobject<UCableComponent>(TEXT("HookCable"));
	hookCable->bAttachEnd = false;
	hookCable->SetHiddenInGame(true);
	hookCable->SetupAttachment(RootComponent);
	hookCable->SetWorldLocation(GetActorLocation());

	// Movement states
	bIsHanging = false;
	bIsClimbing = false;
	bIsSprinting = false;
	bIsDashing = false;
	bIsSwinging = false;

	// Reset interaction flag
	bCanInteract = false;

	// Reset available upgrade option
	availableUpgrade = EMovementUpgrade::MU_NULL;

	// Reset upgrade object
	upgradeActor = nullptr;

	// Reset upgrade variables
	bIsDoubleJumpUpgrade = false;
	bIsTripleJumpUpgrade = false;
	bIsSprintUpgrade = false;
	bIsDashUpgrade = false;
	bIsHookUpgrade = false;

	// Teleporting
	currentTeleporter = nullptr;
	bCanTeleport = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AThirdPersonProto1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AThirdPersonProto1Character::ToggleCrouch);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonProto1Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonProto1Character::MoveRight);

	// Pause menu
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AThirdPersonProto1Character::TogglePauseMenu);

	// Interaction with objects
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AThirdPersonProto1Character::Interact);

	// Hanging/climbing
	PlayerInputComponent->BindAction("ClimbUp", IE_Pressed, this, &AThirdPersonProto1Character::ClimbUp);
	PlayerInputComponent->BindAction("DropDown", IE_Pressed, this, &AThirdPersonProto1Character::DropDown);

	// Sprinting
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AThirdPersonProto1Character::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AThirdPersonProto1Character::StopSprinting);

	// Dashing
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AThirdPersonProto1Character::StartDashing);

	// Hook
	PlayerInputComponent->BindAction("Hook", IE_Pressed, this, &AThirdPersonProto1Character::ToggleHook);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AThirdPersonProto1Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThirdPersonProto1Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AThirdPersonProto1Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AThirdPersonProto1Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AThirdPersonProto1Character::OnResetVR);
}

void AThirdPersonProto1Character::NotifyActorBeginOverlap(AActor* OtherActor)
{
	 // Check to see if OtherActor is a movement upgrade
	 AMovementUpgrade* upgrade = Cast<AMovementUpgrade>(OtherActor);
	 if (upgrade) {

		  // Get type of upgrade
		  availableUpgrade = upgrade->typeOfUpgrade;

		  // Keep track of upgrade actor
		  upgradeActor = upgrade;

		  // Enable interaction
		  bCanInteract = true;
	 }

	 // Check to see if OtherActor is a hook point trigger volume
	 AHookPoint* hookPoint = Cast<AHookPoint>(OtherActor);
	 if (hookPoint) {

		  // Use hook point
		  currentHookPointInRange = hookPoint;
	 }

	 // Check to see if OtherActor is a teleporter trigger volume
	 ATeleporter* teleporter = Cast<ATeleporter>(OtherActor);
	 if (teleporter) {

		  // Keep track of this teleporter for use in case player decides to teleport
		  currentTeleporter = teleporter;

		  // Enable interaction
		  bCanInteract = true;
	 }
}

void AThirdPersonProto1Character::NotifyActorEndOverlap(AActor* OtherActor)
{
	 // Perform if just left an upgrade volume trigger
	 if (Cast<AMovementUpgrade>(OtherActor)) {
		  // Reset available upgrade option
		  availableUpgrade = EMovementUpgrade::MU_NULL;

		  // Reset upgrade actor
		  upgradeActor = nullptr;
	 }

	 // Perform if just left a hook point volume trigger
	 if (Cast<AHookPoint>(OtherActor)) {

		  // Discard hook point reference
		  currentHookPointInRange = nullptr;
	 }

	 // Perform if just left a teleporter volume trigger
	 if (Cast<ATeleporter>(OtherActor)) {

		  // DIscard teleporter reference
		  currentTeleporter = nullptr;
	 }

	 // Reset interaction flag
	 bCanInteract = false;
}

void AThirdPersonProto1Character::Landed(const FHitResult& Hit)
{
	 // Reset dashing ability if cooldown has passed
	 if (!GetWorldTimerManager().IsTimerActive(dashingTimerHandle)) {
		  bDidDash = false;
	 }
}

// Tick
void AThirdPersonProto1Character::Tick(float DeltaTime)
{
	 StartHanging();

	 // Perform swinging calculations if character is swinging
	 if (bIsSwinging) {
		  FVector characterVelocity = GetVelocity();
		  FVector hookDirection = currentHookPointBeingUsed->GetActorLocation() - GetActorLocation();
		  float swingAngleForce = FVector::DotProduct(hookDirection, characterVelocity);
		  hookDirection.Normalize();
		  GetCharacterMovement()->AddForce(hookDirection * swingAngleForce * -20.0f);
	 }

	 /*
	 // Hook debug
	 if (currentHookPointInRange) {

		  // Debug draw the trace
		  DrawDebugLine(GetWorld(), GetActorLocation(), currentHookPointInRange->GetActorLocation(), FColor::Orange);
	 }
	 */
}

void AThirdPersonProto1Character::TogglePauseMenu()
{
	 if (bIsPauseMenuOpen) {
		  ClosePauseMenu();
	 }
	 else {
		  OpenPauseMenu();
	 }
}

void AThirdPersonProto1Character::OpenPauseMenu_Implementation()
{
	 // Set flag
	 bIsPauseMenuOpen = true;
}

void AThirdPersonProto1Character::ClosePauseMenu_Implementation()
{
	 // Set flag
	 bIsPauseMenuOpen = false;
}

void AThirdPersonProto1Character::Interact()
{
	 // Perform only if currently able to interact
	 if (!bCanInteract) {
		  return;
	 }

	 // Teleport
	 if (currentTeleporter) {
		  TeleportTo(currentTeleporter->GetTeleportTargetLocation(), GetActorRotation());
	 }

	 // Receive upgrade
	 switch (availableUpgrade) {
		  default:
		  case EMovementUpgrade::MU_NULL:
				break;
		  case EMovementUpgrade::MU_DOUBLE_JUMP:
				if (UpgradeToDoubleJump() && upgradeActor) {
					 upgradeActor->Collect();
				}
				break;
		  case EMovementUpgrade::MU_TRIPLE_JUMP:
				if (UpgradeToTripleJump() && upgradeActor) {
					 upgradeActor->Collect();
				}
				break;
		  case EMovementUpgrade::MU_SPRINT:
				if (UpgradeToSprint() && upgradeActor) {
					 upgradeActor->Collect();
				}
				break;
		  case EMovementUpgrade::MU_DASH:
				if (UpgradeToDash() && upgradeActor) {
					 upgradeActor->Collect();
				}
				break;
		  case EMovementUpgrade::MU_HOOK:
				if (UpgradeToHook() && upgradeActor) {
					 upgradeActor->Collect();
				}
				break;
	 }
}

void AThirdPersonProto1Character::SetIsHanging(bool newIsHanging)
{
	 bIsHanging = newIsHanging;
}

bool AThirdPersonProto1Character::GetIsHanging()
{
	 return bIsHanging;
}


void AThirdPersonProto1Character::OnResetVR()
{
	// If ThirdPersonProto1 is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in ThirdPersonProto1.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AThirdPersonProto1Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AThirdPersonProto1Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AThirdPersonProto1Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonProto1Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonProto1Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && !bIsHanging)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AThirdPersonProto1Character::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) && !bIsHanging )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

// Handle crouching
void AThirdPersonProto1Character::ToggleCrouch() {

	 // Don't allow crouch if character is jumping, falling or hanging
	 if (GetCharacterMovement()->IsFalling() || bIsHanging) {
		  UnCrouch();
		  return;
	 }
	 
	 // Check whether the character is already crouching
	 if (GetCharacterMovement()->IsCrouching()) {
		  UnCrouch();
	 }
	 else {
		  bIsSprinting = false; // Stop sprinting, just in case character happens to be sprinting
		  Crouch();
	 }
}

bool AThirdPersonProto1Character::ForwardTrace()
{

	 // Set parameters for trace
	 FHitResult outHit;
	 const float traceLength = 150.0f;
	 const FVector start = GetActorLocation();
	 const FVector end = GetActorLocation() + GetActorForwardVector() * traceLength;
	 const float sphereTraceRadius = 10.0f;
	 const FCollisionShape sphere = FCollisionShape::MakeSphere(sphereTraceRadius);
	 FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("ForwardTraceParam")), false, this); // Maybe bInTraceComplex = true will allow much more climbing?
	 FCollisionResponseParams traceResponseParams = FCollisionResponseParams();

	 // Create trace
	 const bool hit = GetWorld()->SweepSingleByChannel(outHit, start, end, FQuat::Identity, ECC_Visibility, sphere, traceParams, traceResponseParams);

	 // Debug draw the trace
	 FColor debugColor = FColor::Red;

	 // Collect information from the trace if it hits
	 bool forwardTraceCheck = false;
	 if (hit) {

		  // Get hit object info
		  hangingWallLocation = outHit.Location;
		  hangingWallNormal = outHit.Normal;

		  // Return successful check
		  forwardTraceCheck = true;

		  // Debug draw the trace
		  debugColor = FColor::Green;
		  //UE_LOG(LogClass, Log, TEXT("HIT"));
		  //GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, FString::Printf(TEXT("Hit: %s"), *outHit.Actor->GetName()));
	 }

	 // Debug draw the trace
	 DrawDebugLine(GetWorld(), start, end, debugColor);

	 // Return check
	 return forwardTraceCheck;
}

bool AThirdPersonProto1Character::HeightTrace()
{

	 // Set parameters for trace
	 FHitResult outHit;
	 const FVector start = GetActorLocation() + FVector(0.0f, 0.0f, 300.0f) + GetActorForwardVector() * 75.0f;
	 const FVector end = start - FVector(0.0f, 0.0f, 300.0f);
	 const float sphereTraceRadius = 10.0f;
	 const FCollisionShape sphere = FCollisionShape::MakeSphere(sphereTraceRadius);
	 FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("HeightTraceParam")), false, this);
	 FCollisionResponseParams traceResponseParams = FCollisionResponseParams();

	 // Create trace
	 const bool hit = GetWorld()->SweepSingleByChannel(outHit, start, end, FQuat::Identity, ECC_Visibility, sphere, traceParams, traceResponseParams);

	 // Debug draw the trace
	 FColor debugColor = FColor::Red;

	 // Collect information from the trace if it hits
	 bool withinRange = false;
	 bool heightTraceCheck = false;
	 if (hit) {

		  // Get hit object info
		  hangingWallHeight = outHit.Location;

		  // Check whether hit location is in range
		  //const USkeletalMeshSocket *pelvisSocket = GetMesh()->GetSocketByName("pelvisSocket");
		  const FVector pelvisSocketLocation = GetMesh()->GetSocketLocation("pelvisSocket");
		  if (hangingWallHeight.Z - pelvisSocketLocation.Z >= minHangHeight && hangingWallHeight.Z - pelvisSocketLocation.Z <= maxHangHeight) {

				// Return successful check
				heightTraceCheck = true;
		  }

		  // Debug draw the trace
		  debugColor = FColor::Green;
	 }

	 // Debug draw the trace
	 DrawDebugLine(GetWorld(), start, end, debugColor);

	 // Return check
	 return heightTraceCheck;
}

void AThirdPersonProto1Character::StartHanging()
{
	 // Don't perform if hanging is on cooldown or character is crouching, sprinting, dashing, swinging or already hanging
	 if (!bCanHang || bIsCrouched || bIsHanging || bIsSprinting || bIsDashing || bIsSwinging) {
		  return;
	 }

	 // Check forward trace
	 if (!ForwardTrace()) {
		  return;
	 }

	 // Check height trace
	 if (!HeightTrace()) {
		  return;
	 }

	 // Go into hanging mode
	 bCanHang = false;
	 bIsHanging = true;
	 GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying); // Change movememnt mode to flying (allows hovering in the air)
	 GetCharacterMovement()->StopMovementImmediately(); // Stop moving

	 // Start hanging animation
	 GetMesh()->GetAnimInstance()->Montage_Play(hangingMontage, 0.0f);
	 GetMesh()->GetAnimInstance()->Montage_Pause(hangingMontage);

	 // Set character location and orientation
	 FVector distanceFromWall = hangingWallNormal * 20.0f + hangingWallLocation;
	 FVector targetLocation = FVector(distanceFromWall.X, distanceFromWall.Y, hangingWallHeight.Z - 80.0f);
	 FRotator targetRotation = UKismetMathLibrary::MakeRotFromX(hangingWallNormal * -1);
	 //SetActorLocationAndRotation(targetLocation, targetRotation, false);
	 FLatentActionInfo latentActionInfo;
	 latentActionInfo.CallbackTarget = this;
	 UKismetSystemLibrary::MoveComponentTo(GetRootComponent(), targetLocation, targetRotation, true, true, 0.2, false, EMoveComponentAction::Move, latentActionInfo);
}

void AThirdPersonProto1Character::ClimbUp()
{

	 // Perform only if character is hanging
	 if (!bIsHanging) {
		  return;
	 }

	 // Perform only if character is not yet climbing
	 if (bIsClimbing) {
		  return;
	 }

	 // Play climbing animation
	 GetMesh()->GetAnimInstance()->Montage_Play(hangingMontage);
	 bIsClimbing = true;

	 // Climbing animation montage has a custom notify that will trigger StopHanging()
}

void AThirdPersonProto1Character::DropDown()
{

	 // Perform only if character is hanging and not climbing
	 if (!bIsHanging || bIsClimbing) {
		  return;
	 }

	 // Stop hanging and fall down
	 bIsHanging = false;
	 GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
	 GetWorldTimerManager().SetTimer(hangingTimerHandle, this, &AThirdPersonProto1Character::ResetHangingCooldown, hangingCooldown, false);

	 // Stop hanging animation
	 GetMesh()->GetAnimInstance()->Montage_Stop(0.2, hangingMontage);
}

void AThirdPersonProto1Character::StopHanging()
{

	 // Move forwwards a little so that character is not hovering (maybe should be address in animation itself instead)
	 FVector targetLocation = GetRootComponent()->GetComponentLocation() + GetActorForwardVector() * 50.0f;
	 FRotator targetRotation = UKismetMathLibrary::MakeRotFromX(GetActorForwardVector());
	 FLatentActionInfo latentActionInfo;
	 latentActionInfo.CallbackTarget = this;
	 UKismetSystemLibrary::MoveComponentTo(GetRootComponent(), targetLocation, targetRotation, true, true, 0.2, false, EMoveComponentAction::Move, latentActionInfo);

	 // Stop hanging and restore movement
	 bCanHang = true;
	 bIsClimbing = false;
	 bIsHanging = false;
	 GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AThirdPersonProto1Character::ResetHangingCooldown()
{
	 bCanHang = true;
}

void AThirdPersonProto1Character::StartSprinting()
{
	 // Perform is character is not crouching, hanging, climbing, swinging or already sprinting and if the upgrade has been unlocked
	 if (bIsSprintUpgrade && !bIsCrouched && !bIsHanging && !bIsSwinging && !bIsSprinting) {

		  // Change running speed
		  GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;

		  // Start sprinting
		  bIsSprinting = true;
	 }
}

void AThirdPersonProto1Character::StopSprinting()
{
	 // Perform only if sprinting
	 if (!bIsSprinting) {
		  return;
	 }

	 // Reset running speed
	 GetCharacterMovement()->MaxWalkSpeed = nonSprintSpeed;

	 // Stop sprinting
	 bIsSprinting = false;
}

void AThirdPersonProto1Character::StartDashing()
{
	 // Perform only if the upgrade has been unlocked and not crouching, hanging, climbing, swinging or already dashing, and if the ability is not on cooldown
	 if (bIsDashUpgrade && !bDidDash && !bIsCrouched && !bIsHanging && !bIsSwinging && !bIsDashing) {

		  // Get rid of friction
		  GetCharacterMovement()->BrakingFrictionFactor = 0.0f;

		  // Launch the character
		  LaunchCharacter(FVector(GetActorForwardVector().X, GetActorForwardVector().Y, 0).GetSafeNormal() * dashDistance, true, true);

		  // Play the dash sound
		  UGameplayStatics::PlaySoundAtLocation(GetWorld(), dashSound, GetActorLocation());

		  // Start dashing
		  bIsDashing = true;
		  bDidDash = true;

		  // Set timer to stop dashing
		  GetWorldTimerManager().SetTimer(dashingTimerHandle, this, &AThirdPersonProto1Character::StopDashing, dashingTime, false);
	 }
}

void AThirdPersonProto1Character::StopDashing()
{
	 // Perform only if dashing
	 if (bIsDashing) {

		  // Bring back friction
		  GetCharacterMovement()->BrakingFrictionFactor = defaultBreakingFrictionFactor;

		  // Stop momentum and add slower momentum
		  GetCharacterMovement()->StopMovementImmediately();
		  LaunchCharacter(FVector(GetActorForwardVector().X, GetActorForwardVector().Y, 0).GetSafeNormal() * dashStopSpeed, true, true);

		  // Stop dashing
		  bIsDashing = false;

		  // Set timer to reset dashing
		  GetWorldTimerManager().SetTimer(dashingTimerHandle, this, &AThirdPersonProto1Character::ResetDashing, dashingCooldown, false);
	 }
}

void AThirdPersonProto1Character::ResetDashing()
{
	 // Perform only if not jumping or falling
	 if (!GetCharacterMovement()->IsFalling()) {

		  // Reset dashing ability
		  bDidDash = false;
	 }
}

void AThirdPersonProto1Character::ToggleHook()
{
	 // If already swinging, stop swinging
	 if (bIsSwinging) {
		  StopSwinging();
	 }
	 // Perform only if not crouching, hanging or climbing, if a hook point has been found and if the upgrade has been activated
	 else if (bIsHookUpgrade && !bIsCrouched && !bIsHanging && currentHookPointInRange) {
		  StartSwinging();
	 }
}

void AThirdPersonProto1Character::StartSwinging()
{
	 // Assume current movement state has already been checked

	 // Perform if hook point has been found
	 if (!currentHookPointInRange) {
		  return;
	 }

	 // Play hook sound 
	 UGameplayStatics::PlaySoundAtLocation(GetWorld(), hookSound, GetActorLocation());

	 // Set cable hook properties
	 currentHookPointBeingUsed = currentHookPointInRange;
	 hookCable->bAttachEnd = true;
	 hookCable->SetAttachEndTo(currentHookPointBeingUsed, FName());
	 hookCable->SetHiddenInGame(false);

	 // Start swinging
	 bIsSwinging = true;
}

void AThirdPersonProto1Character::StopSwinging()
{
	 // Stop swinging
	 bIsSwinging = false;

	 // Reset cable hook properties
	 hookCable->SetHiddenInGame(true);
	 hookCable->bAttachEnd = false;
	 currentHookPointBeingUsed = nullptr;
}

bool AThirdPersonProto1Character::UpgradeToDoubleJump()
{
	 // Update upgrade flag
	 bIsDoubleJumpUpgrade = true;

	 // Increase max number of jumps for the character
	 JumpMaxCount = 2;

	 // Play upgrade pickup sound
	 UGameplayStatics::PlaySoundAtLocation(GetWorld(), upgradePickupSound, GetActorLocation());

	 // Successful upgrade
	 return true;
}

bool AThirdPersonProto1Character::UpgradeToTripleJump()
{
	 // Upgrade only if double jump upgrade has already been activated
	 if (bIsDoubleJumpUpgrade) {

		  // Update upgrade flag
		  bIsTripleJumpUpgrade = true;

		  // Increase max number of jumps for the character
		  JumpMaxCount = 3;

		  // Play upgrade pickup sound
		  UGameplayStatics::PlaySoundAtLocation(GetWorld(), upgradePickupSound, GetActorLocation());

		  // Successful upgrade
		  return true;
	 }

	 // Unsucessful upgrade
	 return false;
}

bool AThirdPersonProto1Character::UpgradeToSprint()
{
	 // Update upgrade flag
	 bIsSprintUpgrade = true;

	 // Play upgrade pickup sound
	 UGameplayStatics::PlaySoundAtLocation(GetWorld(), upgradePickupSound, GetActorLocation());

	 // Successful upgrade
	 return true;
}

bool AThirdPersonProto1Character::UpgradeToDash()
{
	 // Upgrade only if sprint upgrade has already been activated
	 if (bIsSprintUpgrade) {

		  // Update upgrade flag
		  bIsDashUpgrade = true;

		  // Play upgrade pickup sound
		  UGameplayStatics::PlaySoundAtLocation(GetWorld(), upgradePickupSound, GetActorLocation());

		  // Successful upgrade
		  return true;
	 }

	 // Unsuccessful upgrade
	 return false;
}

bool AThirdPersonProto1Character::UpgradeToHook()
{
	 // Update upgrade flag
	 bIsHookUpgrade = true;

	 // Play upgrade pickup sound
	 UGameplayStatics::PlaySoundAtLocation(GetWorld(), upgradePickupSound, GetActorLocation());

	 // Successful upgrade
	 return true;
}
