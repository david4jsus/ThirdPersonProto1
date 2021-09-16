// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveKey.h"
#include "Components/SphereComponent.h"
#include "ObjectiveComponent.h"
#include "KeyPressurePlate.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROTO1_API AKeyPressurePlate : public AInteractiveKey
{
	GENERATED_BODY()

public:

	 // Mesh for the pressure plate
	 UPROPERTY(visibleAnywhere, Category = "Mesh")
	 UStaticMeshComponent* PressurePlateMesh;

	 // Trigger volume for the pressure plate
	 UPROPERTY(VisibleAnywhere, Category = "Trigger Volume")
	 USphereComponent* TriggerVolume;

	 // Trigger volume radius
	 UPROPERTY(EditAnywhere, Category = "Trigger Volume")
	 float TriggerVolumeRadius;

	 // Reference to the obstacle to lock/unlock
	 UPROPERTY(EditAnywhere, Category = "Obstacle")
	 AInteractiveObstacle* ConnectedObstacle;

protected:

private:

	 // Component to interact with the objective system
	 UPROPERTY(VisibleAnywhere, Category = "Objective Component")
	 UObjectiveComponent* objectiveComponent;

public:

	 // Sets default values for this actor's properties
	 AKeyPressurePlate();

protected:

	 // Called when the game starts or when spawned
	 virtual void BeginPlay() override;

	 // Unlock an active and locked InteractiveObstacle object
	 virtual void Unlock(AInteractiveObstacle* obstacle) override;

	 // Lock an active and unlocked InteractiveObstacle object
	 virtual void Lock(AInteractiveObstacle* obstacle) override;

	 // What happens when volume is triggered (unlock the connected obstacle)
	 UFUNCTION(BlueprintCallable, Category = "Trigger Volume")
	 void EnterTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	 // What happens when volume is exited (lock the connected obstacle)
	 UFUNCTION(BlueprintCallable, Category = "Trigger Volume")
	 void ExitTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	
};
