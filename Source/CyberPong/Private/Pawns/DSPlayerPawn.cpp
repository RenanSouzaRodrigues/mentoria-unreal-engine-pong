// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/DSPlayerPawn.h"

// Sets default values
ADSPlayerPawn::ADSPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADSPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADSPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADSPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

