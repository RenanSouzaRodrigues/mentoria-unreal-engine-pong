// Mentoria Unreal Engine - 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DSPlayerPawn.generated.h"

class UBoxComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class CYBERPONG_API ADSPlayerPawn : public APawn {
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category="Player Components")
	UBoxComponent* PlayerCollision;
	
	UPROPERTY(EditAnywhere, Category="Player Components")
	UStaticMeshComponent* PlayerBox;
	
	
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
	
	
protected:
	UPROPERTY(EditAnywhere, Category="Player Movement")
	float MovementSpeed;
	
private:
	UFUNCTION()
	void MovePlayer(const FInputActionValue& InputActionValue);
};