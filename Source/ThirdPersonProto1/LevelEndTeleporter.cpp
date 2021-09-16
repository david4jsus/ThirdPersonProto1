// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelEndTeleporter.h"
#include "Components/SphereComponent.h"
#include "ObjectiveComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelEndTeleporter::ALevelEndTeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set up teleporter mesh
	teleporterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeleporterMesh"));
	SetRootComponent(teleporterMesh);

	// Set up trigger volume
	TriggerVolumeRadius = 80.0f;
	triggerVolume = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerVolume"));
	triggerVolume->SetSphereRadius(TriggerVolumeRadius);
	triggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ALevelEndTeleporter::EnterTriggerVolume);
	triggerVolume->SetupAttachment(GetRootComponent());
	FVector triggerVolumePosition = GetRootComponent()->GetComponentLocation() + FVector(0.0f, 0.0f, 110.0f);
	triggerVolume->SetWorldLocation(triggerVolumePosition);

	// Set up objective component
	objectiveComponent = CreateDefaultSubobject<UObjectiveComponent>(TEXT("ObjectiveComponent"));
}

// Called every frame
/*void ALevelEndTeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

void ALevelEndTeleporter::TeleportToNextLevel()
{
	 // The next of the level to teleport to
	 FName nextLevel;

	 // Get the name of the current level
	 FString currentLevel = UGameplayStatics::GetCurrentLevelName(GetWorld());

	 // Get the name of the next level based on the current level's name
	 if (currentLevel.Compare("ThirdPersonExampleMap") == 0) {
		  nextLevel = FName("MovementTestMap");
	 }
	 else if (currentLevel.Compare("MovementTestMap") == 0) {
		  nextLevel = FName("ObstaclesTestMap");
	 }
	 else if (currentLevel.Compare("ObstaclesTestMap") == 0) {
		  nextLevel = FName("ThirdPersonExampleMap");
	 }
	 else {
		  return;
	 }

	 // Teleport to the nextlevel
	 UGameplayStatics::OpenLevel(GetWorld(), nextLevel);
}

// Called when the game starts or when spawned
void ALevelEndTeleporter::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ALevelEndTeleporter::IsFinalObjectiveComplete()
{
	 // Check the completion status of the final objective
	 return objectiveComponent->IsObjectiveComplete(FName("obj3"));
}

void ALevelEndTeleporter::EnterTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	 // Check the completion status of the final objective in the level
	 if (!IsFinalObjectiveComplete()) {
		  return;
	 }

	 // If the condition is met, teleport to the next level
	 TeleportToNextLevel();
}
