// Mentoria Unreal Engine - 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DSPlayerPawn.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class CYBERPONG_API ADSPlayerPawn : public APawn {
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category="Player Inputs")
	UInputMappingContext* PlayerInputMappingContext;	

	UPROPERTY(EditAnywhere, Category="Player Inputs")
	UInputAction* MovementInputAction;
	
public:
	ADSPlayerPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UFUNCTION()
	void MovePlayer(const FInputActionValue& InputActionValue);
};