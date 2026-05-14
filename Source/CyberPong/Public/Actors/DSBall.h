// Mentoria Unreal Engine - 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSBall.generated.h"

class UNiagaraSystem;
class UDSGameDataPDA;
class UDSGameDatabasePDA;
class USphereComponent;

UCLASS()
class CYBERPONG_API ADSBall : public AActor {
	GENERATED_BODY()

	// ==================================================
	// GAME DATABASE
	// ==================================================
protected:
	UPROPERTY(EditAnywhere, Category="Game Database")
	TObjectPtr<UDSGameDatabasePDA> GameDatabase;
	
	
	// ==================================================
	// GAME DATA
	// ==================================================
protected:
	UPROPERTY(EditAnywhere, Category="Actor Properties - Game Data")
	TObjectPtr<UDSGameDataPDA> GameData;
	
	
	// ==================================================
	// ACTOR COMPONENTS
	// ==================================================
protected:
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<USphereComponent> BallCollision;
	
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UStaticMeshComponent> BallMesh;
	

	// ==================================================
	// UNREAL LIFECYCLE METHODS
	// ==================================================
public:
	ADSBall();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	
	// ==================================================
	// BALL SPEED
	// ==================================================
private:
	void InitializeBallSpeed();
	void IncreaseBallSpeed();
	
	
	// ==================================================
	// BALL HIT
	// ==================================================
protected:
	UPROPERTY(EditAnywhere, Category="Actor Properties - Ball Hit")
	TObjectPtr<USoundBase> BallHitSound;
	
	UPROPERTY(EditAnywhere, Category="Actor Properties - Ball Hit")
	TObjectPtr<UNiagaraSystem> BallHitParticles;
	
	UPROPERTY(EditAnywhere, Category="Actor Properties - Ball Hit")
	TSubclassOf<UCameraShakeBase> PlayerHitCameraShake;
	
	UPROPERTY(EditAnywhere, Category="Actor Properties - Ball Hit")
	TSubclassOf<UCameraShakeBase> ObstacleHitCameraShake;
	
	UPROPERTY(EditAnywhere, Category="Actor Properties - Ball Hit")
	
private:
	UPROPERTY(Transient)
	TObjectPtr<APlayerCameraManager> PlayerCameraManager;
	
private:
	UFUNCTION()
	void OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void PlayBallHitSound();
	void PlayBallHitParticles(const FVector& Location, const FVector& Direction);
};
