// Mentoria Unreal Engine - 2026


#include "Actors/DSBall.h"
#include "NiagaraFunctionLibrary.h"
#include "Actors/DSObstacle.h"
#include "Components/SphereComponent.h"
#include "Data/DSGameDatabasePDA.h"
#include "Data/DSGameDataPDA.h"
#include "Kismet/GameplayStatics.h"
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
	
	this->PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this->GetWorld(), 0);
	
	if (!this->PlayerCameraManager) {
		DSDebug::ErrorMessage("Ball Erro: Player Camera Manager is invalid or null");
		return;
	}
	
	this->GameData->ClearValues();
	
	this->BallCollision->OnComponentHit.AddDynamic(this, &ThisClass::OnBallHit);
	
	this->InitializeBallSpeed();
}

void ADSBall::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


// ==================================================
// BALL SPEED
// ==================================================
void ADSBall::InitializeBallSpeed() {
	const FVector InitialDirection = FVector(1.0f, 1.0f, 0.0f).GetSafeNormal();
	const float InitialSpeed = this->GameDatabase->BallInitialSpeed;
	this->BallCollision->SetPhysicsLinearVelocity(InitialDirection * InitialSpeed);
}

void ADSBall::IncreaseBallSpeed() {
	const FVector CurrentVelocity = this->BallCollision->GetPhysicsLinearVelocity();

	if (CurrentVelocity.IsNearlyZero()) return;
	
	const FVector Direction = CurrentVelocity.GetSafeNormal();

	const float CurrentSpeed = CurrentVelocity.Size();

	const float NewSpeed = FMath::Clamp(
		CurrentSpeed + this->GameDatabase->BallSpeedIncreasePerHit,
		this->GameDatabase->BallMinSpeed,
		this->GameDatabase->BallMaxSpeed
	);

	this->BallCollision->SetPhysicsLinearVelocity(Direction * NewSpeed);
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
	this->IncreaseBallSpeed();
	
	// Sempre que a bola bate em algum lugar, tbm é tocado um som de impacto
	this->PlayBallHitSound();
	
	if (OtherActor->ActorHasTag("Player")) {
		if (this->PlayerCameraManager) {
			this->PlayerCameraManager->StartCameraShake(this->PlayerHitCameraShake);
		}
	}
	
	if (OtherActor->ActorHasTag("Enemy")) {
		
	}
	
	if (OtherActor->ActorHasTag("Obstacle")) {
		if (const auto obstacle = Cast<ADSObstacle>(OtherActor)) {
			DSDebug::SuccessMessage("Obstacle Destroyed");
			obstacle->DestroyObstacle();
		}
		
		if (this->PlayerCameraManager) {
			this->PlayerCameraManager->StartCameraShake(this->ObstacleHitCameraShake);
		}
		
		return;
	}
	
	this->PlayBallHitParticles(Hit.Location, Hit.Normal);
}


void ADSBall::PlayBallHitSound() {
	if (!this->BallHitSound) {
		DSDebug::ErrorMessage("Ball Error: Invalid sound to play on hit");
		return;
	}
	UGameplayStatics::PlaySound2D(this->GetWorld(), this->BallHitSound);
}

void ADSBall::PlayBallHitParticles(const FVector& Location, const FVector& Direction) {
	if (!this->BallHitParticles) {
		DSDebug::ErrorMessage("Ball Error: Invalid ball hit particles to spawn");
		return;
	}
	
	const auto rotation = Direction.Rotation();
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this->GetWorld(), this->BallHitParticles, Location, rotation);
}