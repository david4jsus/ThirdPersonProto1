// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelEndTeleporter.generated.h"

// Forward declarations
class USphereComponent;
class UObjectiveComponent;

UCLASS()
class THIRDPERSONPROTO1_API ALevelEndTeleporter : public AActor
{
	GENERATED_BODY()
	
public:

	 UPROPERTY(EditAnywhere, Category = "Trigger Volume")
	 float TriggerVolumeRadius;

private:

	 UPROPERTY(VisibleAnywhere, Category = "Mesh")
	 UStaticMeshComponent* teleporterMesh;

	 UPROPERTY(VisibleAnywhere, Category = "Trigger Volume")
	 USphereComponent* triggerVolume;

	 UPROPERTY()
	 UObjectiveComponent* objectiveComponent;

public:

	// Sets default values for this actor's properties
	ALevelEndTeleporter();

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Teleport to the next level
	UFUNCTION(BlueprintCallable, Category = "End Level Teleporter")
	void TeleportToNextLevel();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Check for the win condition before teleporting away
	UFUNCTION(BlueprintPure, Category = "End Level Teleporter")
	bool IsFinalObjectiveComplete();

	// Check for final objective completion and transition to next level if condition is met
	UFUNCTION(BlueprintCallable, Category = "Trigger Volume")
	void EnterTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
