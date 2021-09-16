// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveObstacle.h"
#include "InteractiveKey.generated.h"

UCLASS()
class THIRDPERSONPROTO1_API AInteractiveKey : public AActor
{
	GENERATED_BODY()

public:

protected:

	 // Unlock an active and locked InteractiveObstacle object
	 UFUNCTION(BlueprintCallable, Category = "Key")
	 virtual void Unlock(AInteractiveObstacle* obstacle);

	 // Lock an active and unlocked InteractiveObstacle object
	 UFUNCTION(BlueprintCallable, Category = "Key")
	 virtual void Lock(AInteractiveObstacle* obstacle);

private:
	
public:

	// Sets default values for this actor's properties
	AInteractiveKey();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

};
