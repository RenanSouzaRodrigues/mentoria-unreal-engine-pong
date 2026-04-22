// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DSGameDataPDA.h"


void UDSGameDataPDA::ClearValues() {
	this->PlayerPoints = 0;
	this->PlayerScore = 0;
	this->EnemyScore = 0;
}

void UDSGameDataPDA::IncrementePlayerPoints(const uint64 Amount) {
	this->PlayerPoints += Amount;
	this->OnUpdatePlayerPoints.ExecuteIfBound();
}

void UDSGameDataPDA::IncrementPlayerScore() {
	this->PlayerScore++;
	this->OnUpdateGameScore.ExecuteIfBound();
}

void UDSGameDataPDA::IncrementEnemyScore() {
	this->EnemyScore++;
	this->OnUpdateGameScore.ExecuteIfBound();
}
