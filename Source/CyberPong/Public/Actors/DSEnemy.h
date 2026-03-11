// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSEnemy.generated.h"

class UDSGameDatabasePDA;
class UBoxComponent;

UCLASS()
class CYBERPONG_API ADSEnemy : public AActor {
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Enemy Components")
	TObjectPtr<UBoxComponent> EnemyCollision;
	
	UPROPERTY(EditAnywhere, Category="Enemy Components")
	TObjectPtr<UStaticMeshComponent> EnemyBox;
	
protected:
	UPROPERTY(EditAnywhere, Category="Game Database")
	TObjectPtr<UDSGameDatabasePDA> GameDatabase;
	
protected:
	UPROPERTY(EditAnywhere, Category="Ball Reference")
	TObjectPtr<AActor> BallReferenceActor;
	
public:
	// Sets default values for this actor's properties
	ADSEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private: 
	void MoveEnemy(const float deltaTime);
};
