// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "EMovementUpgrade.h"
#include "ObjectiveComponent.h"
#include "MovementUpgrade.generated.h"

UCLASS()
class THIRDPERSONPROTO1_API AMovementUpgrade : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMovementUpgrade();

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Return the mesh for the upgrade
	UFUNCTION(BlueprintCallable, Category = "Upgrade")
		 UStaticMeshComponent* GetMesh() const;

	// Return the volume for the upgrade
	UFUNCTION(BlueprintCallable, Category = "Upgrade Volume")
		 USphereComponent* GetInteractionVolume() const;

	// Return the volume radius for the upgrade
	UFUNCTION(BlueprintCallable, Category = "Upgrade Volume")
		 float GetInteractionVolumeRadius() const;

	// Set the volume radius for the upgrade
	UFUNCTION(BlueprintCallable, Category = "Upgrade Volume")
		 void SetVolumeRadius(float newRadius);

	// What happens when the upgrade is collected
	UFUNCTION(BlueprintCallable, Category = "Upgrade")
		 void Collect();

	// Upgrade interaction text
	UPROPERTY(EditAnywhere, Category = "Upgrade Text")
		 FString triggerText;

	// Whether the volume is triggered
	UPROPERTY(VisibleAnywhere, Category = "Upgrade Volume")
		 bool bIsVolumeTriggered;

	UPROPERTY(EditAnywhere, Category = "Upgrade")
		 EMovementUpgrade typeOfUpgrade;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Show upgrade text when character triggers volume (what happens when volume is triggered)
	UFUNCTION(BlueprintCallable, Category = "Upgrade Volume")
	void TriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Stop showing upgrade text when character triggers volume (what happens when volume is exited)
	UFUNCTION(BlueprintCallable, Category = "Upgrade Volume")
		 void ExitVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	 // Static mesh to represent upgrade in the level
	 UPROPERTY(VisibleAnywhere,/* BlueprintReadOnly, meta = (AllowPrivateAccess = "true")*/ Category = "Upgrade")
		  UStaticMeshComponent* upgradeMesh;

	 // Trigger volume for this actor
	 UPROPERTY(VisibleAnywhere,/* BlueprintReadOnly, meta = (AllowPrivateAccess = "true")*/ Category = "Upgrade")
		  USphereComponent* interactionVolume;

	 // Radius of the volume trigger
	 float interactionVolumeRadius;

	 // Component to interact with the objective system
	 UPROPERTY(VisibleAnywhere, Category = "Objective Component")
	 UObjectiveComponent* objectiveComponent;
};
