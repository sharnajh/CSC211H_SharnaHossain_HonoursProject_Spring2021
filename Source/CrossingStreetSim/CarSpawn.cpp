// Fill out your copyright notice in the Description page of Project Settings.

#include "CarSpawn.h"
#include "Engine/World.h"

// Sets default values
ACarSpawn::ACarSpawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACarSpawn::BeginPlay()
{
	Super::BeginPlay();

	const FVector Location = {0,0,0};
	const FRotator Rotation = GetActorRotation();

	GetWorld()->SpawnActor<AActor>(CarSpawn, Location, Rotation);
}

// Called every frame
void ACarSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
