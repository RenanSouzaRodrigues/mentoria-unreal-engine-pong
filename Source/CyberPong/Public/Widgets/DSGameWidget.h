// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSGameWidget.generated.h"

class UDSGameDataPDA;
class UTextBlock;

UCLASS()
class CYBERPONG_API UDSGameWidget : public UUserWidget {
	GENERATED_BODY()
	
	
	// ===========================================================
	// GAME DATA
	// ===========================================================
protected:
	UPROPERTY(EditAnywhere, Category="Game Data")
	TObjectPtr<UDSGameDataPDA> GameData;
	
	
	// ===========================================================
	// WIDGET COMPONENTS
	// ===========================================================
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> PlayerPointsCounterText;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> GameScoreCounterText;
	
	
	// ===========================================================
	// UNREAL LIFECYCLE METHODS
	// ===========================================================
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	
	// ===========================================================
	// SCORE HANDLING
	// ===========================================================
private:
	UFUNCTION()
	void UpdatePlayerPoints();
	void UpdateGameScore();
};