// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DSObstacleSpawner.h"
#include "Actors/DSObstacle.h"
#include "Utils/DSDebug.h"


// Sets default values
ADSObstacleSpawner::ADSObstacleSpawner() {
	PrimaryActorTick.bCanEverTick = true;
}

void ADSObstacleSpawner::BeginPlay() {
	Super::BeginPlay();
	
	FTimerHandle timerHandle;
	
	// depois de 5 segudos, spawna o nosso obstaculo
	const auto timerDelegateCallback = [this]() -> void {
		this->SpawnObstacles();
	};
	
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda(timerDelegateCallback);
	
	this->GetWorldTimerManager().SetTimer(timerHandle, timerDelegate, this->timerAmount, true);
}

void ADSObstacleSpawner::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ADSObstacleSpawner::SpawnObstacles() {
	if (this->spawnCount > 0) return;
	
	this->spawnCount = 0;
	
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	
	const auto spawnRotation = FRotator::ZeroRotator;
	
	for (auto count = 1; count <= this->InitialSpawnAmount; count++) {
		const auto randomIndex = FMath::RandRange(0, this->SpawnLocations.Num() - 1);
		
		if (!this->SpawnLocations.IsValidIndex(randomIndex)) {
			DSDebug::ErrorMessage("Invalid index when trying to spawn obstacle");
			return;
		}
		
		const auto spawnLocation = this->SpawnLocations[randomIndex]->GetActorLocation();
		
		this->GetWorld()->SpawnActor<ADSObstacle>(this->ObstacleClassToSpawn, spawnLocation, spawnRotation, spawnParams);
		this->spawnCount++;
	}
	
	this->InitialSpawnAmount += this->SpawnIncrementalAmount;
}

void ADSObstacleSpawner::DecreaseSpawnCount() {
	if (this->spawnCount == 0) return;
	this->spawnCount--;
}
