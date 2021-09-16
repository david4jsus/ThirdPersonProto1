// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportVolume.generated.h"

// Forward declarations
class UBoxComponent;

UCLASS()
class THIRDPERSONPROTO1_API ATeleportVolume : public AActor
{
	GENERATED_BODY()
	
public:

	 UPROPERTY(VisibleAnywhere, Category = "Trigger Volume")
	 UBoxComponent* TriggerVolume;

	 UPROPERTY(EditAnywhere, Category = "Teleport Location")
	 FVector TeleportLocation;

public:
	// Sets default values for this actor's properties
	ATeleportVolume();

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Teleport the player to the our teleport location
	UFUNCTION(BlueprintCallable, Category = "Trigger Volume")
	void EnterTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
