// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DSGameDataPDA.generated.h"

DECLARE_DELEGATE(FOnGameDataUpdate);

UCLASS()
class CYBERPONG_API UDSGameDataPDA : public UPrimaryDataAsset {
	GENERATED_BODY()
	
public:
	FOnGameDataUpdate OnUpdatePlayerPoints;
	FOnGameDataUpdate OnUpdateGameScore;
	
public:
	UPROPERTY(EditAnywhere, Category="Game")
	uint64 PlayerPoints { 0 };
	
	UPROPERTY(EditAnywhere, Category="Game")
	uint8 PlayerScore { 0 };
	
	UPROPERTY(EditAnywhere, Category="Game")
	uint8 EnemyScore { 0 };
	
	
public:
	UFUNCTION(CallInEditor)
	void ClearValues();
	
	void IncrementePlayerPoints(const uint64 Amount);
	void IncrementPlayerScore();
	void IncrementEnemyScore();
};
