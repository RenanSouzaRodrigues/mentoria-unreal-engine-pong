// Mentoria Unreal Engine - 2026

#include "Pawns/DSPlayerPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ADSPlayerPawn::ADSPlayerPawn() {
	PrimaryActorTick.bCanEverTick = true;
}

void ADSPlayerPawn::BeginPlay() {
	Super::BeginPlay();
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
	// aqui é onde a gente move nosso cubo
}