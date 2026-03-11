// Mentoria Unreal Engine - 2026


#include "Actors/DSBall.h"
#include "Components/SphereComponent.h"
#include "Data/DSGameDatabasePDA.h"
#include "Utils/DSDebug.h"


ADSBall::ADSBall() {
	PrimaryActorTick.bCanEverTick = true;
	
	this->BallCollision = this->CreateDefaultSubobject<USphereComponent>("Ball Collision");
	this->BallCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	this->BallCollision->SetSimulatePhysics(true);
	this->BallCollision->SetUseCCD(true);
	this->SetRootComponent(this->BallCollision);
	
	this->BallMesh = this->CreateDefaultSubobject<UStaticMeshComponent>("Ball Mesh");
	this->BallMesh->SetupAttachment(this->BallCollision);
}

void ADSBall::BeginPlay() {
	Super::BeginPlay();
	
	if (!this->GameDatabase) {
		DSDebug::ErrorMessage("Ball Error: game database invalido ou nulo");
		return;
	}
	
	const float initialForce = this->GameDatabase->BallInitialImpulse;
	const auto force = FVector(initialForce);
	this->BallCollision->AddForce(force);
	
}

void ADSBall::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}