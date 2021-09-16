// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionTextWidget.h"

UInteractionTextWidget::UInteractionTextWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UInteractionTextWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UInteractionTextWidget::UpdateText(FString newText)
{
    // Make sure our widget exists
    if (TXTInteraction) {

        // Update the text
        TXTInteraction->SetText(FText::FromString(newText));
    }
}

void UInteractionTextWidget::SetWidgetVisible(bool visible)
{
    // Make sure our widget exists
    if (TXTInteraction) {

        // Set visibility
        if (visible) {
            TXTInteraction->SetVisibility(ESlateVisibility::Visible);
        }
        else {
            TXTInteraction->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void UInteractionTextWidget::UpdateObjectiveText(FString newText)
{
    // Make sure our widget exists
    if (TXTObjective) {

        // Update the text
        TXTObjective->SetText(FText::FromString(newText));
    }
}

void UInteractionTextWidget::SetObjectiveTextVisible(bool visible)
{
    // Make sure our widget exists
    if (TXTObjective) {

        // Set visibility
        if (visible) {
            TXTObjective->SetVisibility(ESlateVisibility::Visible);
        }
        else {
            TXTObjective->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}
