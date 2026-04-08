// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSObstacleSpawner.generated.h"

class ADSObstacle;

UCLASS()
class CYBERPONG_API ADSObstacleSpawner : public AActor {
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Spawn Properties")
	TSubclassOf<ADSObstacle> ObstacleClassToSpawn;
	
	UPROPERTY(EditAnywhere, Category="Spawn Properties")
	TArray<TObjectPtr<AActor>> SpawnLocations;
	
	UPROPERTY(EditAnywhere, Category="Spawn Properties")
	uint8 InitialSpawnAmount { 3 };
	
	UPROPERTY(EditAnywhere, Category="Spawn Properties")
	uint8 SpawnIncrementalAmount { 1 };
	
	UPROPERTY(EditAnywhere, Category="Spawn Properties - Debug")
	float timerAmount { 5 };
	
private:
	uint8 spawnCount;
	
public:
	ADSObstacleSpawner();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	
private:
	void SpawnObstacles();
	
public:
	void DecreaseSpawnCount();
	
};
