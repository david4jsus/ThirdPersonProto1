// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectiveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONPROTO1_API UObjectiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	 // (Optional) The name of the specific objective to advance
	 UPROPERTY(EditAnywhere, Category = "Objective System")
	 FName objectiveName;

public:
	// Sets default values for this component's properties
	UObjectiveComponent();

	// Attempt to progress the current objective
	UFUNCTION(BlueprintCallable, Category = "Objective System")
	void ProgressCurrentObjective();

	// Attempt to progress the objective with the specified name
	UFUNCTION(BlueprintCallable, Category = "Objective System")
	void ProgressObjectiveByName();

	// Check the completion status of an objective
	UFUNCTION(BlueprintPure, Category = "Objective System")
	bool IsObjectiveComplete(FName objectiveToCheck);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
