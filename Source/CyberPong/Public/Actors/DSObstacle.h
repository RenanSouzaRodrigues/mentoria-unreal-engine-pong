// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSObstacle.generated.h"

class URotatingMovementComponent;

UCLASS()
class CYBERPONG_API ADSObstacle : public AActor {
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UStaticMeshComponent> ObstacleMesh;
	
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<URotatingMovementComponent> RotationComponent;
	
	
public:
	ADSObstacle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
public:
	void DestroyObstacle();
};
