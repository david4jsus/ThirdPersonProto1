// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"

AInGameHUD::AInGameHUD()
{
}

void AInGameHUD::BeginPlay()
{
    Super::BeginPlay();

    // Instantiate widget objects (except in the main menu level)
    if (UGameplayStatics::GetCurrentLevelName(GetWorld()).Compare("MainMenu") != 0 && InteractionTextWidgetClass) {
        InteractionTextWidget = CreateWidget<UInteractionTextWidget>(GetWorld(), InteractionTextWidgetClass);

        // If success, add to the viewport
        if (InteractionTextWidget) {
            InteractionTextWidget->AddToViewport();
        }
    }
}

void AInGameHUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AInGameHUD::DrawHUD()
{
    Super::DrawHUD();
}

void AInGameHUD::UpdateAndShowInteractionText(FString newText)
{
    // Check that the widget has been created successfully
    if (InteractionTextWidget) {

        // Update the widget's text and visibility
        InteractionTextWidget->UpdateText(newText);
        InteractionTextWidget->SetWidgetVisible(true);
    }
}

void AInGameHUD::HideInteractionText()
{
    // Check that the widget has been created successfully
    if (InteractionTextWidget) {

        // Update the widget's visibility
        InteractionTextWidget->SetWidgetVisible(false);
    }
}

void AInGameHUD::ShowObjectiveText()
{
    // Check that the widget has been created successfully
    if (InteractionTextWidget) {

        // Update the widget's visibility
        InteractionTextWidget->SetObjectiveTextVisible(true);
    }
}

void AInGameHUD::HideObjectiveText()
{
    // Check that the widget has been created successfully
    if (InteractionTextWidget) {

        // Update the widget's visibility
        InteractionTextWidget->SetObjectiveTextVisible(false);
    }
}

void AInGameHUD::UpdateObjectiveText(FString newText)
{
    // Check that the widget has been created successfully
    if (InteractionTextWidget) {
        
        // Update the widget's text
        InteractionTextWidget->UpdateObjectiveText(newText);
    }
}

void AInGameHUD::UpdateAndShowObjectiveText(FString newText)
{
    // Check that the widget has been created successfully
    if (InteractionTextWidget) {

        // Update the widget's text and visibility
        InteractionTextWidget->UpdateObjectiveText(newText);
        InteractionTextWidget->SetObjectiveTextVisible(true);
    }
}
