// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DSPlayerController.generated.h"

class UDSGameWidget;

UCLASS()
class CYBERPONG_API ADSPlayerController : public APlayerController {
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category="Controller Properties - Game Widget")
	TSubclassOf<UUserWidget> GameWidgetClass;
	
private:
	UPROPERTY(Transient)
	TObjectPtr<UDSGameWidget> GameWidgetInstance;
	
	
protected:
	virtual void BeginPlay() override;
};
