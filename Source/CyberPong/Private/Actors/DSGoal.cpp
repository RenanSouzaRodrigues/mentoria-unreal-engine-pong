// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DSGoal.h"
#include "Components/BoxComponent.h"
#include "Data/DSGameDataPDA.h"
#include "Utils/DSDebug.h"


ADSGoal::ADSGoal() {
	PrimaryActorTick.bCanEverTick = true;
	
	this->GoalCollision = this->CreateDefaultSubobject<UBoxComponent>("Goal Collision");
}

void ADSGoal::BeginPlay() {
	Super::BeginPlay();
	
	if (!this->GameData) {
		DSDebug::ErrorMessage("Goal Erro: Game data is not defined");
		return;
	}
	
	this->GoalCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::DetectBall);
}

void ADSGoal::Tick(const float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ADSGoal::DetectBall(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult) {
	DSDebug::InfoMessage("Gooooooooool");
	
	if (!this->GameData || !OtherActor->ActorHasTag("Ball")) return;
	
	if (this->GoalType == EDSGoalType::Player) {
		this->GameData->IncrementEnemyScore();
		return;
	}
	
	this->GameData->IncrementPlayerScore();
}