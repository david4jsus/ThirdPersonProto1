// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementUpgrade.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUD.h"

// Sets default values
AMovementUpgrade::AMovementUpgrade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the static mesh component
	upgradeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UpgradeMesh"));
	RootComponent = upgradeMesh;

	// Create the sphere volume component
	interactionVolumeRadius = 100.0f;
	interactionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("UpgradeInteractionVolume"));
	interactionVolume->SetSphereRadius(interactionVolumeRadius);
	interactionVolume->OnComponentBeginOverlap.AddDynamic(this, &AMovementUpgrade::TriggerVolume);
	interactionVolume->OnComponentEndOverlap.AddDynamic(this, &AMovementUpgrade::ExitVolume);
	interactionVolume->SetupAttachment(GetRootComponent());
	FVector initialInteractionVolumePosition = GetRootComponent()->GetComponentLocation() + GetRootComponent()->GetForwardVector() * 10.0f;
	interactionVolume->SetWorldLocation(initialInteractionVolumePosition);
	bIsVolumeTriggered = false;

	// Trigger text for the upgrade
	triggerText = "Press the interaction key to interact with this object";

	// Initialize type of upgrade
	typeOfUpgrade = EMovementUpgrade::MU_NULL;

	// Initialize the objective system component
	objectiveComponent = CreateDefaultSubobject<UObjectiveComponent>(TEXT("ObjectiveComponent"));
}

// Called when the game starts or when spawned
void AMovementUpgrade::BeginPlay()
{
	Super::BeginPlay();
}

void AMovementUpgrade::TriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	 if (OtherActor && (OtherActor != this) && OtherComp) {
		  bIsVolumeTriggered = true;

		  // Interact with the HUD to show the interaction text
		  AInGameHUD* InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		  if (InGameHUD) {
				InGameHUD->UpdateAndShowInteractionText(triggerText);
		  }
	 }
}

void AMovementUpgrade::ExitVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	 if (OtherActor && (OtherActor != this) && OtherComp) {
		  bIsVolumeTriggered = false;

		  // Interact with the HUD to hide the interaction text
		  AInGameHUD* InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		  if (InGameHUD) {
				InGameHUD->HideInteractionText();
		  }
	 }
}

// Called every frame
/*void AMovementUpgrade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}*/

UStaticMeshComponent* AMovementUpgrade::GetMesh() const
{
	 return upgradeMesh;
}

USphereComponent* AMovementUpgrade::GetInteractionVolume() const
{
	 return interactionVolume;
}

float AMovementUpgrade::GetInteractionVolumeRadius() const
{
	 return interactionVolumeRadius;
}

void AMovementUpgrade::SetVolumeRadius(float newRadius)
{
	 interactionVolumeRadius = newRadius;
}

void AMovementUpgrade::Collect()
{
	 // Progress the objective system
	 if (objectiveComponent) {
		  objectiveComponent->ProgressObjectiveByName();
	 }

	 // Destroy this object
	 Destroy();
}
