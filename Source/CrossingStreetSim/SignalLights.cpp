// Fill out your copyright notice in the Description page of Project Settings.

#include "SignalLights.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/FileHelper.h"

// Sets default values for this component's properties
USignalLights::USignalLights()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USignalLights::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("%i"), GetWorld()->GetActorCount());
	TArray<UStaticMeshComponent *> Components;
	GetOwner()->GetComponents<UStaticMeshComponent>(Components);
	for (int32 i = 0; i < Components.Num(); i++)
	{
		UStaticMeshComponent *StaticMeshComponent = Components[i];
	}
	StaticMesh = Components[0];

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	Go = false;
	Timer = 0;
}

// Called every frame
void USignalLights::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// if (TriggerLight && TriggerLight->IsOverlappingActor(Player))
	// {
	// 	Lights();
	// }
	// else
	// {
	// 	StaticMesh->SetMaterial(0, StopMaterial);
	// }
	Lights();
}

void USignalLights::Lights()
{
	if (Go)
	{
		StaticMesh->SetMaterial(0, GoMaterial);
		if (RoadBlock)
		{
			// Disable Collission
			RoadBlock->SetActorEnableCollision(false);
		}
	}
	else
	{
		StaticMesh->SetMaterial(0, StopMaterial);
		if (RoadBlock)
		{
			// Enable Collission
			RoadBlock->SetActorEnableCollision(true);
			RecordFailedAttempt();
		}
	}

	Timer++;

	if (Timer >= 500)
	{
		Go = !Go;
		Timer = 0;
	}
}

void USignalLights::RecordFailedAttempt()
{
	FString AttemptsPath = FPaths::ProjectConfigDir();
	AttemptsPath.Append(TEXT("Attempts.txt"));
	IPlatformFile &FileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (FileManager.FileExists(*AttemptsPath))
	{
		FString AttemptsHeader(TEXT("X"));
		if (FFileHelper::SaveStringToFile(AttemptsHeader, *AttemptsPath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append))
		{
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to write FString to file."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempts.txt not found!"));
	}
}