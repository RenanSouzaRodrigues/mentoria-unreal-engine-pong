// Mentoria Unreal Engine - 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSBall.generated.h"

class UDSGameDatabasePDA;
class USphereComponent;

UCLASS()
class CYBERPONG_API ADSBall : public AActor {
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<USphereComponent> BallCollision;
	
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UStaticMeshComponent> BallMesh;
	
protected:
	UPROPERTY(EditAnywhere, Category="Game Database")
	TObjectPtr<UDSGameDatabasePDA> GameDatabase;
	
public:
	ADSBall();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
