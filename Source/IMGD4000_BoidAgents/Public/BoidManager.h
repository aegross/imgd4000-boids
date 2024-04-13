// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoidActor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoidManager.generated.h"

UCLASS()
class IMGD4000_BOIDAGENTS_API ABoidManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoidManager();

	UPROPERTY(VisibleAnywhere)
	TArray<ABoidActor*> boidList;

	UPROPERTY(VisibleAnywhere)
	int numBoids;

	UPROPERTY(EditAnywhere)
	float locationScale;
	UPROPERTY(EditAnywhere)
	float velocityScale;
	UPROPERTY(EditAnywhere)
	float bufferDistance;
	UPROPERTY(EditAnywhere)
	int speedLimit;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// public functions
	FVector ruleOne(ABoidActor* currentBoid);
	FVector ruleTwo(ABoidActor* currentBoid);
	FVector ruleThree(ABoidActor* currentBoid);

private:
	// private attributes
	UWorld* world;

	// private functions
	void spawnBoids();
	void updateBoidLocations();
	FVector limitSpeed(FVector velocity); // selected tweak
};
