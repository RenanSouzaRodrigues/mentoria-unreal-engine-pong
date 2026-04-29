// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/DSPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Utils/DSDebug.h"
#include "Widgets/DSGameWidget.h"

void ADSPlayerController::BeginPlay() {
	Super::BeginPlay();
	
	if (!this->GameWidgetClass) {
		DSDebug::ErrorMessage("Player Controller Error: Game Widget Class is not defined");
		return;
	}
	
	const auto createdWidget = CreateWidget(this, this->GameWidgetClass);
	
	if (!createdWidget) {
		DSDebug::ErrorMessage("Player Controller Error: Game Widget was not created");
		return;
	}
	
	this->GameWidgetInstance = Cast<UDSGameWidget>(createdWidget);
	
	if (!this->GameWidgetInstance) {
		DSDebug::ErrorMessage("Player Controller Error: Game Widget instance is invalid or null");
		return;
	}
	
	this->GameWidgetInstance->AddToViewport();
}