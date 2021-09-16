// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportVolume.h"
#include "Components/BoxComponent.h"
#include "ThirdPersonProto1Character.h"

// Sets default values
ATeleportVolume::ATeleportVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set up trigger volume
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TeleportVolumeTriggerVolume"));
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATeleportVolume::EnterTriggerVolume);
	SetRootComponent(TriggerVolume);
}

// Called when the game starts or when spawned
void ATeleportVolume::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
/*void ATeleportVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

void ATeleportVolume::EnterTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	 // Make sure that the other actor is the player character
	 AThirdPersonProto1Character* player = Cast<AThirdPersonProto1Character>(OtherActor);
	 if (!player) return;

	 // Teleport the player to our teleport location
	 player->TeleportTo(TeleportLocation, player->GetActorRotation());
}
