// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DSObstacle.h"

#include "NiagaraFunctionLibrary.h"
#include "Actors/DSObstacleSpawner.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/DSDebug.h"


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
	
	this->PlayDestroyObstacleSound();
	this->PlayDestroyObstacleParticles();
	
	this->Destroy();
}

void ADSObstacle::PlayDestroyObstacleSound() {
	if (!this->DestroyObstacleSound) {
		DSDebug::ErrorMessage("Obstacle Error: Invalid sound to play on destroy");
		return;
	}
	UGameplayStatics::PlaySound2D(this->GetWorld(), this->DestroyObstacleSound);
}

void ADSObstacle::PlayDestroyObstacleParticles() {
	if (!this->DestroyObstacleParticles) {
		DSDebug::ErrorMessage("Obstacle Error: invalid particles to spawn");
		return;
	}
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this->GetWorld(), this->DestroyObstacleParticles, this->GetActorLocation(), this->GetActorRotation());
}
