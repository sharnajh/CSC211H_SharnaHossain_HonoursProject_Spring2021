// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CarSpawn.generated.h"

UCLASS()
class CROSSINGSTREETSIM_API ACarSpawn : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACarSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> CarSpawn;
};
