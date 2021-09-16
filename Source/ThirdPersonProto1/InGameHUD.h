// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "InteractionTextWidget.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROTO1_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	 // Constructor
	 AInGameHUD();

	 // What happens when this class is created ini the level
	 virtual void BeginPlay() override;

	 // Main loop for the HUD
	 virtual void DrawHUD() override;

	 // Tick
	 virtual void Tick(float DeltaSeconds) override;

	 // Start showing interaction text
	 UFUNCTION()
	 void UpdateAndShowInteractionText(FString newText);

	 // Stop showing interaction text
	 UFUNCTION()
	 void HideInteractionText();

	 // Start showing the objective text
	 UFUNCTION()
	 void ShowObjectiveText();

	 // Stop showing the objective text
	 UFUNCTION()
	 void HideObjectiveText();

	 // Update objective text
	 UFUNCTION()
	 void UpdateObjectiveText(FString newText);

	 // Update objective text and start showing it
	 UFUNCTION()
	 void UpdateAndShowObjectiveText(FString newText);

	 // The interaction text widget
	 UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	 TSubclassOf<UUserWidget> InteractionTextWidgetClass;

private:
	 
	 // Instance of the interaction text widget (which becomes instantiated based on InteractionTextWidgetClass being available)
	 UInteractionTextWidget* InteractionTextWidget;

	 // Instance of the objective text widget
};
