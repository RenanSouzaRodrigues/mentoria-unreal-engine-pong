// Mentoria Unreal Engine - 2026


#include "Actors/DSBall.h"
#include "Actors/DSObstacle.h"
#include "Components/SphereComponent.h"
#include "Data/DSGameDatabasePDA.h"
#include "Data/DSGameDataPDA.h"
#include "Utils/DSDebug.h"


// ==================================================
// UNREAL LIFECYCLE METHODS
// ==================================================
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
	
	if (!this->GameData) {
		DSDebug::ErrorMessage("Ball Error: game data is not defined");
		return;
	}
	
	this->GameData->ClearValues();
	
	const float initialForce = this->GameDatabase->BallInitialImpulse;
	const auto force = FVector(initialForce);
	this->BallCollision->AddForce(force);
	
	this->BallCollision->OnComponentHit.AddDynamic(this, &ThisClass::OnBallHit);
}

void ADSBall::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}



// ==================================================
// BALL HIT
// ==================================================
void ADSBall::OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	DSDebug::SuccessMessage("HIT");
	
	if (this->GameData) {
		this->GameData->IncrementePlayerPoints(10);
	}
	
	// Aqui é adicionado o impulso na bola sempre que ela bate em alguma coisa. -Renan
	const auto impulse = this->GameDatabase->BallHitImpulse;
	const auto ballVelocity = this->GetVelocity();
	this->BallCollision->AddImpulse(ballVelocity * impulse);

	if (OtherActor->ActorHasTag("Player")) {
		
	}
	
	if (OtherActor->ActorHasTag("Enemy")) {
		
	}
	
	if (OtherActor->ActorHasTag("Obstacle")) {
		if (const auto obstacle = Cast<ADSObstacle>(OtherActor)) {
			DSDebug::SuccessMessage("Obstacle Destroied");
			obstacle->DestroyObstacle();
		}
	}
}
