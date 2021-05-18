// Fill out your copyright notice in the Description page of Project Settings.

#include "VRCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Misc/FileHelper.h"

// Sets default values
AVRCharacter::AVRCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	// VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("ofjsdjfkd: %s"), *GetName());
	// FVector StartingLocation = GetOwner()->GetActorLocation();
	// GetOwner()->SetActorLocation(StartingLocation);
	// UE_LOG(LogTemp, Error, TEXT("%s"), *GetActorLocation().ToString());
	// UE_LOG(LogTemp, Error, TEXT("%s"), *GetOwner()->GetActorLocation().ToString());
	CameraInput = FVector2D(0.f, 0.f);

	MovementComponent = GetCharacterMovement();
	MovementComponent->MaxWalkSpeed = MaxSpeed;

	// initialize attempts file located in Config directory (INPUT OUTPUT)
	FString AttemptsPath = FPaths::ProjectConfigDir();
	AttemptsPath.Append(TEXT("Attempts.txt"));
	IPlatformFile &FileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (FileManager.FileExists(*AttemptsPath))
	{
		FString AttemptsHeader(TEXT("User Attempts\n"));
		if (FFileHelper::SaveStringToFile(AttemptsHeader, *AttemptsPath))
		{
			UE_LOG(LogTemp, Warning, TEXT("Successfully Written: \"%s\" to the text file"), *AttemptsHeader);
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

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = Camera->GetRelativeRotation();
	NewRotation.Yaw += CameraInput.X;
	Camera->SetRelativeRotation(NewRotation);
}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AVRCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AVRCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &AVRCharacter::LookRight);
}

void AVRCharacter::MoveForward(float throttle)
{
	AddMovementInput(throttle * Camera->GetForwardVector());
}

void AVRCharacter::MoveRight(float throttle)
{
	AddMovementInput(throttle * Camera->GetRightVector());
}

void AVRCharacter::LookRight(float AxisValue)
{
	CameraInput.X = AxisValue;
}
