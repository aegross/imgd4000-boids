// Fill out your copyright notice in the Description page of Project Settings.

#include "BoidManager.h"

// Sets default values
ABoidManager::ABoidManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set attributes
	world = GetWorld();

	// initialize "control" variables (default values picked through testing)
	locationScale = 500;
	velocityScale = 50;
	bufferDistance = 125.0f;
	speedLimit = 15;
}

// Called when the game starts or when spawned
void ABoidManager::BeginPlay()
{
	Super::BeginPlay();

	// spawn all boids
	spawnBoids();

	// get the size of the boid list and store it
	numBoids = boidList.Num();
}

// Called every frame
void ABoidManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// update all boid positions
	updateBoidLocations();
}

// custom private functions

void ABoidManager::spawnBoids() {
	// placement variables
	float spacing = 250.0f; // cm
	float zDefault = 250.0f;
	float zRange = 100.0f;
	
	// make a grid of boids
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (world != nullptr) {
				// determine spawn location and rotation necessary. location has partially randomized z value
				FVector spawnLocation = FVector(i*spacing, j*spacing, FMath::FRandRange(zDefault-zRange, zDefault+zRange));
				FRotator spawnRotation = FRotator();

				// spawn boid actor
				ABoidActor* boid = world->SpawnActor<ABoidActor>(spawnLocation, spawnRotation);

				// add actor to list
				boidList.Add(boid);
			}
		}
	}
}

void ABoidManager::updateBoidLocations() {
	// vector variables
	FVector ruleOneVector = FVector();
	FVector ruleTwoVector = FVector();
	FVector ruleThreeVector = FVector();
	FVector limitedVelocity = FVector();
	
	// for every single boid, calculate rule values and add them to velocity
	for (ABoidActor* boidActor : boidList) {
		ruleOneVector = ruleOne(boidActor);
		ruleTwoVector = ruleTwo(boidActor);
		ruleThreeVector = ruleThree(boidActor);

		boidActor->velocity = boidActor->velocity + ruleOneVector + ruleTwoVector + ruleThreeVector;
		limitedVelocity = limitSpeed(boidActor->velocity); // implemented tweak
		boidActor->SetActorLocation(boidActor->GetActorLocation() + limitedVelocity);
	}
}

// custom public functions

FVector ABoidManager::ruleOne(ABoidActor* currentBoid) {
	FVector boidAvgLoc = FVector();

	// add all (but current) locations together
	for (ABoidActor* boid : boidList) {
		if (boid != currentBoid) {
			boidAvgLoc += boid->GetActorLocation();
		}
	}

	// divide by # of boids (-1 for not including current)
	boidAvgLoc = boidAvgLoc / (numBoids-1);

	// adjust by current boid properties and scalar to be fit for addition later
	return (boidAvgLoc - currentBoid->GetActorLocation()) / locationScale;
}

FVector ABoidManager::ruleTwo(ABoidActor* currentBoid) {
	FVector distanceVector = FVector();

	// if boids are close to each other (euclidian distance <= bufferDistance, adjust position)
	for (ABoidActor* boid : boidList) {
		if (boid != currentBoid) {
			// if boid is close to another object, adjust vector 
			if (FMath::Abs(FVector::Distance(boid->GetActorLocation(), currentBoid->GetActorLocation())) <= bufferDistance) {
				distanceVector = distanceVector - (boid->GetActorLocation() - currentBoid->GetActorLocation());
			}
		}
	}

	// return distance adjusted
	return distanceVector / velocityScale; // so they don't zoom into the ether
}


FVector ABoidManager::ruleThree(ABoidActor* currentBoid) {
	FVector boidAvgVelocity = FVector();

	// add all (but current) velocities (custom value) together
	for (ABoidActor* boid : boidList) {
		if (boid != currentBoid) {
			boidAvgVelocity += boid->velocity;
		}
	}

	// divide by # of boids (-1 for not including current)
	boidAvgVelocity = boidAvgVelocity / (numBoids-1);

	// adjust by current boid properties and scalar to be fit for addition later
	return (boidAvgVelocity - currentBoid->velocity) / velocityScale;
}

FVector ABoidManager::limitSpeed(FVector velocity) {
	FVector limitedVelocity = velocity;

	// velocity.size() is the magnitude of the vector
	if (FMath::Abs(velocity.Size()) > speedLimit) {
		// create unit vector and scale by speed limit
		limitedVelocity = (limitedVelocity / FMath::Abs(limitedVelocity.Size())) * speedLimit;
	}

	// return the adjusted velocity
	return limitedVelocity;
}


