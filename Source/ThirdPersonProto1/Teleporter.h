// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Teleporter.generated.h"

UCLASS()
class THIRDPERSONPROTO1_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	 // Show upgrade text when character triggers volume (what happens when volume is triggered)
	 UFUNCTION(BlueprintCallable, Category = "Trigger Volume")
	 void EnterTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	 // Stop showing upgrade text when character triggers volume (what happens when volume is exited)
	 UFUNCTION(BlueprintCallable, Category = "Trigger Volume")
	 void ExitTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	 // Get the teleport target location
	 UFUNCTION(BlueprintPure)
	 FVector GetTeleportTargetLocation() const;

	 // Set the teleport target location
	 UFUNCTION(BlueprintCallable)
	 void SetTeleportTargetLocation(FVector newLocation);

public:

	 // The location that this teleporter will teleport the character to
	 UPROPERTY(EditAnywhere, Category = "Teleport Location")
	 FVector TeleportTarget;

	 // The text that the UI will show when the character enters the trigger volume
	 UPROPERTY(EditAnywhere, Category = "Teleport Text")
	 FString TriggerText;

	 // The radius of the volume trigger
	 UPROPERTY(EditAnywhere, Category = "Trigger Volume")
	 float TriggerVolumeRadius;

protected:

	 // This actor's mesh
	 UPROPERTY(VisibleAnywhere, Category = "Mesh")
	 UStaticMeshComponent* TeleporterMesh;

	 // The volume that will allow interaction with the character
	 UPROPERTY(VisibleAnywhere, Category = "Trigger Volume")
	 USphereComponent* TriggerVolume;
};
