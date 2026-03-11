// Mentoria Unreal Engine - 2026

#include "Pawns/DSPlayerPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "Data/DSGameDatabasePDA.h"
#include "Utils/DSDebug.h"

ADSPlayerPawn::ADSPlayerPawn() {
	PrimaryActorTick.bCanEverTick = true;
	
	const auto rootComponent = this->CreateDefaultSubobject<USceneComponent>("Root Component");
	this->SetRootComponent(rootComponent);
	
	this->PlayerCollision = this->CreateDefaultSubobject<UBoxComponent>("Player Collision");
	this->PlayerCollision->SetupAttachment(rootComponent);
	
	this->PlayerBox = this->CreateDefaultSubobject<UStaticMeshComponent>("Player Box");
	this->PlayerBox->SetupAttachment(this->PlayerCollision);
}

void ADSPlayerPawn::BeginPlay() {
	Super::BeginPlay();
	
	if (!this->GameDatabase) {
		DSDebug::ErrorMessage("Player Pawn Error: game database invalido ou nulo");
	}
}

void ADSPlayerPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ADSPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	auto controller = this->GetController<APlayerController>();
	
	if (!controller) return;
	
	auto localPlayer = controller->GetLocalPlayer();
	
	auto subsystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	
	subsystem->AddMappingContext(this->PlayerInputMappingContext, 0);
	
	auto inputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	inputComponent->BindAction(this->MovementInputAction, ETriggerEvent::Triggered, this, &ThisClass::MovePlayer);
}

void ADSPlayerPawn::MovePlayer(const FInputActionValue& InputActionValue) {
	if (!this->GameDatabase) return;
	
	const float inputValue = InputActionValue.Get<float>();
	const float deltaTime = this->GetWorld()->GetDeltaSeconds();
	
	// pega a movement speed do player  direto do nosso database.
	const auto movementSpeed = this->GameDatabase->PlayerMovementSpeed;
	
	const FVector newLocation = FVector(0, inputValue, 0) * movementSpeed * deltaTime;
	this->AddActorLocalOffset(newLocation);
}