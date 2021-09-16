// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "HookPoint.generated.h"

UCLASS()
class THIRDPERSONPROTO1_API AHookPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHookPoint();

	// Mesh component for this actor
	UPROPERTY(EditAnywhere, Category = "Mesh")
		 UStaticMeshComponent* hookPointMesh;

	// Trigger volume for this actor
	UPROPERTY(VisibleAnywhere, Category = "Trigger Volume")
		 USphereComponent* triggerVolume;

	// Radius of the trigger volume
	UPROPERTY(EditAnywhere, Category = "Trigger Volume")
		 float triggerVolumeRadius;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
