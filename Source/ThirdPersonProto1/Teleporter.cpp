// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"
#include "InGameHUD.h"

// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set up the actor's mesh
	TeleporterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeleporterMeshComponent"));
	SetRootComponent(TeleporterMesh);

	// Set up the trigger volume
	TriggerVolumeRadius = 80.0f;
	TriggerVolume = CreateDefaultSubobject<USphereComponent>(TEXT("TeleporterTriggerVolume"));
	TriggerVolume->SetSphereRadius(TriggerVolumeRadius);
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::EnterTriggerVolume);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ATeleporter::ExitTriggerVolume);
	TriggerVolume->SetupAttachment(GetRootComponent());
	FVector triggerVolumePosition = GetRootComponent()->GetComponentLocation() + FVector(0.0f, 0.0f, 110.0f);
	TriggerVolume->SetWorldLocation(triggerVolumePosition);

	// Initialize the default trigger text
	TriggerText = "Press 'E' to teleport";
}

// Called every frame
/*void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
}

void ATeleporter::EnterTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	 if (OtherActor && (OtherActor != this) && OtherComp) {

		  // Interact with the HUD to show the interaction text
		  AInGameHUD* InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		  if (InGameHUD) {
				InGameHUD->UpdateAndShowInteractionText(TriggerText);
		  }
	 }
}

void ATeleporter::ExitTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	 if (OtherActor && (OtherActor != this) && OtherComp) {

		  // Interact with the HUD to hide the interaction text
		  AInGameHUD* InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		  if (InGameHUD) {
				InGameHUD->HideInteractionText();
		  }
	 }
}

FVector ATeleporter::GetTeleportTargetLocation() const
{
	 return TeleportTarget;
}

void ATeleporter::SetTeleportTargetLocation(FVector newLocation)
{
	 TeleportTarget = newLocation;
}

