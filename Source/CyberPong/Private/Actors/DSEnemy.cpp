// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DSEnemy.h"
#include "Components/BoxComponent.h"
#include "Data/DSGameDatabasePDA.h"
#include "Utils/DSDebug.h"


// Sets default values
ADSEnemy::ADSEnemy() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	const auto rootComponent = this->CreateDefaultSubobject<USceneComponent>("Root Component");
	this->SetRootComponent(rootComponent);
	
	this->EnemyCollision = this->CreateDefaultSubobject<UBoxComponent>("Enemy Collision");
	this->EnemyCollision->SetupAttachment(rootComponent);
	
	this->EnemyBox = this->CreateDefaultSubobject<UStaticMeshComponent>("Enemy Box");
	this->EnemyBox->SetupAttachment(this->EnemyCollision);
}

// Called when the game starts or when spawned
void ADSEnemy::BeginPlay() {
	Super::BeginPlay();
	
	if (!this->BallReferenceActor) {
		DSDebug::ErrorMessage("Enemy Erro: A referencia da bola e invalida ou nula");
		return;
	}
	
	if (!this->GameDatabase) {
		DSDebug::ErrorMessage("Enemy Error: Game datavase invalido ou nulo");
	}
}

// Called every frame
void ADSEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	this->MoveEnemy(DeltaTime);
}

void ADSEnemy::MoveEnemy(const float deltaTime) {
	if (!this->BallReferenceActor || !this->GameDatabase) return;
	
	const float ballYAxis = this->BallReferenceActor->GetActorLocation().Y;
	
	// Representa o Ponto de partida (A)
	const auto currentLocation = this->GetActorLocation();
	
	// Representa o ponto de chegada (B)
	const auto targetLocation = FVector(currentLocation.X, ballYAxis , currentLocation.Z);
	
	// pega a movement speed do enemy direto do nosso database.
	const auto movementSpeed = this->GameDatabase->EnemyMovementSpeed;
	
	const auto newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, deltaTime, movementSpeed);
	
	this->SetActorLocation(newLocation, true);
	
	auto newActorLocation = this->GetActorLocation();
	newActorLocation.Y = FMath::Clamp(newActorLocation.Y, -200, 200);
	this->SetActorLocation(newActorLocation);
}

