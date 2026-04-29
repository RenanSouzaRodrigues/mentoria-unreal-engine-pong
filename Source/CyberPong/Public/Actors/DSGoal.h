// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSGoal.generated.h"

class UDSGameDataPDA;
class UBoxComponent;

UENUM()
enum class EDSGoalType : uint8 {
	Player, Enemy
};


UCLASS()
class CYBERPONG_API ADSGoal : public AActor {
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category="Actor Properties - Game Data")
	TObjectPtr<UDSGameDataPDA> GameData;
	
protected:
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UBoxComponent> GoalCollision;
	
protected:
	UPROPERTY(EditAnywhere, Category="Actor Properties - Goal Type")
	EDSGoalType GoalType { EDSGoalType::Player };

public:
	ADSGoal();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	
private:
	UFUNCTION()
	void DetectBall(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
