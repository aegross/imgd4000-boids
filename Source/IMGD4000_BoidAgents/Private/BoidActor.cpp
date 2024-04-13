// Fill out your copyright notice in the Description page of Project Settings.

#include "BoidActor.h"

// Sets default values
ABoidActor::ABoidActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set the UStaticMeshComponent to a sphere
	boidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("boidMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	boidMesh->SetStaticMesh(SphereMeshAsset.Object);
	boidMesh->SetWorldScale3D(FVector(0.5f,0.5f,0.5f));

	// set the mesh to be the root component
	RootComponent = boidMesh;

	// set initial velocity semi-randomly
	initVelocityLimit = 5.0f;
	
	velocity = FVector(FMath::FRandRange(-initVelocityLimit, initVelocityLimit),
					FMath::FRandRange(-initVelocityLimit, initVelocityLimit),
					FMath::FRandRange(0.0f, initVelocityLimit)); // only make z required positive
}

// Called when the game starts or when spawned
void ABoidActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABoidActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

