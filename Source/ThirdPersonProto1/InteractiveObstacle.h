// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveObstacle.generated.h"

UCLASS()
class THIRDPERSONPROTO1_API AInteractiveObstacle : public AActor
{
	GENERATED_BODY()

public:

	 // Start active/inactive
	 UPROPERTY(EditAnywhere, Category = "Obstacle Properties")
	 bool StartActive;

	 // Start locked/unlocked
	 UPROPERTY(EditAnywhere, Category = "Obstacle Properties")
	 bool StartLocked;

protected:

private:

	 // Locking and unlocking can only be performed when active
	 bool bIsActive;

	 // Locking/unlocking
	 bool bIsLocked;
	
public:

	// Sets default values for this actor's properties
	AInteractiveObstacle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Get whether this obstacle is active
	UFUNCTION(BlueprintPure, Category = "Obstacle Activation")
	bool GetObstacleActive() const;

	// Activate this obstacle
	UFUNCTION(BlueprintCallable, Category = "Obstacle Activation")
	bool ActivateObstacle();

	// Deactivate this obstacle
	UFUNCTION(BlueprintCallable, Category = "Obstacle Activation")
	bool DeactivateObstacle();

	// Get whether this obstacle is locked
	UFUNCTION(BlueprintPure, Category = "Obstacle Locking")
	bool GetObstacleLocked() const;

	// Lock this obstacle
	UFUNCTION(BlueprintCallable, Category = "Obstacle Locking")
	virtual bool LockObstacle();

	// Unlock this obstacle
	UFUNCTION(BlueprintCallable, Category = "Obstacle Locking")
	virtual bool UnlockObstacle();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
};
