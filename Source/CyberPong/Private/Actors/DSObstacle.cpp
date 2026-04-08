// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DSObstacle.h"

#include "Actors/DSObstacleSpawner.h"
#include "GameFramework/RotatingMovementComponent.h"


ADSObstacle::ADSObstacle() {
	PrimaryActorTick.bCanEverTick = true;
	
	const auto rootComponent = this->CreateDefaultSubobject<USceneComponent>("Root Component");
	this->SetRootComponent(rootComponent);
	
	this->ObstacleMesh = this->CreateDefaultSubobject<UStaticMeshComponent>("Obstacle Mesh");
	this->ObstacleMesh->SetupAttachment(rootComponent);
	
	this->RotationComponent = this->CreateDefaultSubobject<URotatingMovementComponent>("Rotation Component");
}

void ADSObstacle::BeginPlay() {
	Super::BeginPlay();
	
}

void ADSObstacle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ADSObstacle::DestroyObstacle() {
	if (const auto spawner = Cast<ADSObstacleSpawner>(this->GetOwner())) {
		spawner->DecreaseSpawnCount();
	}
	
	this->Destroy();
}
