// Mentoria Unreal Engine - 2026

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DSGameDatabasePDA.generated.h"

UCLASS()
class CYBERPONG_API UDSGameDatabasePDA : public UPrimaryDataAsset {
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="Player")
	float PlayerMovementSpeed;
	
	UPROPERTY(EditAnywhere, Category="Enemy")
	float EnemyMovementSpeed;
	
	UPROPERTY(EditAnywhere, Category="Ball")
	float BallInitialSpeed;
	
	UPROPERTY(EditAnywhere, Category="Ball")
	float BallSpeedIncreasePerHit;
	
	UPROPERTY(EditAnywhere, Category="Ball")
	float BallMinSpeed;
	
	UPROPERTY(EditAnywhere, Category="Ball")
	float BallMaxSpeed;
	
	UPROPERTY(EditAnywhere, Category="Ball")
	float BallHitImpulse;
	
};
