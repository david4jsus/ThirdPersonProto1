// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectiveTrigger.generated.h"

// Forward delcartions
class UBoxComponent;
class UObjectiveComponent;

UCLASS()
class THIRDPERSONPROTO1_API AObjectiveTrigger : public AActor
{
	GENERATED_BODY()

public:

	 // Trigger volume for this actor
	 UPROPERTY(VisibleAnywhere, Category = "Trigger Volume")
	 UBoxComponent* TriggerVolume;

private:

	 // Component to interact with the objective system
	 UPROPERTY(EditAnywhere, Category = "Objective Component")
	 UObjectiveComponent* objectiveComponent;
	
public:	
	// Sets default values for this actor's properties
	AObjectiveTrigger();

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Progress an objective when the character enters this volume
	UFUNCTION(BlueprintCallable, Category = "Trigger Volume")
	void EnterTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
