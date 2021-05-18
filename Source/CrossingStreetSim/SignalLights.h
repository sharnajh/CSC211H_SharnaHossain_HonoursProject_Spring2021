
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/MeshComponent.h"
#include "Materials/Material.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/BlockingVolume.h"
#include "./VRCharacter.h"
#include "SignalLights.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROSSINGSTREETSIM_API USignalLights : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USignalLights();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Lights();
private:
	UPROPERTY(VisibleAnywhere)
	class UMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	ABlockingVolume *RoadBlock;

	UPROPERTY(EditAnywhere)
	class UMaterial* GoMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterial* StopMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterial* DefaultMaterial;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *TriggerLight;

	UPROPERTY(EditAnywhere)
	AActor *Player;

	bool Go;

	int32 Timer;

	TArray<AActor> actorz;

	void RecordFailedAttempt();
	
};
