// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DSGameWidget.h"
#include "Components/TextBlock.h"
#include "Data/DSGameDataPDA.h"
#include "Utils/DSDebug.h"


// ===========================================================
// UNREAL LIFECYCLE METHODS
// ===========================================================
void UDSGameWidget::NativeConstruct() {
	Super::NativeConstruct();
	
	if (!this->PlayerPointsCounterText || !this->GameScoreCounterText) {
		DSDebug::ErrorMessage("Game Widget Error: not all visual componets are defined");
		return;
	}
	
	if (!this->GameData) {
		DSDebug::ErrorMessage("Game Widget Error: game data is not defined");
		return;
	}
	
	this->UpdatePlayerPoints();
	this->UpdateGameScore();
	
	this->GameData->OnUpdateGameScore.BindLambda([this]() -> void {
		this->UpdateGameScore();
	});
	
	this->GameData->OnUpdatePlayerPoints.BindLambda([this]() -> void {
		this->UpdatePlayerPoints();
	});
}

void UDSGameWidget::NativeDestruct() {
	Super::NativeDestruct();
	
	if (this->GameData) {
		this->GameData->OnUpdateGameScore.Unbind();
		this->GameData->OnUpdatePlayerPoints.Unbind();
	}
}


// ===========================================================
// SCORE HANDLING
// ===========================================================
void UDSGameWidget::UpdatePlayerPoints() {
	const auto playerPoints = FString::FromInt(this->GameData->PlayerPoints);
	const auto playerPointsFinalText = "SCORE: " + playerPoints;
	this->PlayerPointsCounterText->SetText(FText::FromString(playerPointsFinalText));
}

void UDSGameWidget::UpdateGameScore() {
	const auto playerScore = FString::FromInt(this->GameData->PlayerScore);
	const auto enemyScore = FString::FromInt(this->GameData->EnemyScore);
	const auto gameScoreFinalText = playerScore + " - " + enemyScore;
	this->GameScoreCounterText->SetText(FText::FromString(gameScoreFinalText));
}