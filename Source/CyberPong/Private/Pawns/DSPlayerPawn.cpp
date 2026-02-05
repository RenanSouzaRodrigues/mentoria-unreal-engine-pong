// Mentoria Unreal Engine - 2026


#include "Pawns/DSPlayerPawn.h"

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
}