// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "InteractionTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROTO1_API UInteractionTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	 // Constructor
	 UInteractionTextWidget(const FObjectInitializer& ObjectInitializer);

	 // UI equivalent of BeginPlay()
	 virtual void NativeConstruct() override;

	 // Update the text of the widget
	 UFUNCTION(BlueprintCallable, Category = "Interaction Text Widget")
	 void UpdateText(FString newText);

	 // Update the visibility of the widget
	 UFUNCTION(BlueprintCallable, Category = "Interaction Text Widget")
	 void SetWidgetVisible(bool visible);

	 // This be for objective text
	 UFUNCTION(BlueprintCallable, Category = "Objective Text Widget")
	 void UpdateObjectiveText(FString newText);

	 // This be for objective text
	 UFUNCTION(BlueprintCallable, Category = "Objective Text Widget")
	 void SetObjectiveTextVisible(bool visible);
	 
	 // Update the text being used in this widget
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Interaction Text WIdget")
	 class UTextBlock* TXTInteraction;

	 // This be objective text
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Objective Text Widget")
	 class UTextBlock* TXTObjective;
};
