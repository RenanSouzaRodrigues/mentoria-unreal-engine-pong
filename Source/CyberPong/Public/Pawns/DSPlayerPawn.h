// Mentoria Unreal Engine - 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DSPlayerPawn.generated.h"

UCLASS()
class CYBERPONG_API ADSPlayerPawn : public APawn {
	GENERATED_BODY()
	
public:
	ADSPlayerPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};