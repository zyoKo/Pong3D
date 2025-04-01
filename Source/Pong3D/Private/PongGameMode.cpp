// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

#include "PongPlayerController.h"
#include "Pong3D/Ball.h"
#include "Pong3D/Paddle.h"

APongGameMode::APongGameMode()
{
	// Set the custom player controller
    PlayerControllerClass = APongPlayerController::StaticClass();

    // Set default pawn to none, since we don't want the player to possess anything
    DefaultPawnClass = nullptr;

	SpectatorClass = nullptr;
}

void APongGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

    // Spawn or find both Paddles
	FindOrSpawnPaddle(EPaddleType::PLAYER_1);
	FindOrSpawnPaddle(EPaddleType::PLAYER_2);
}

void APongGameMode::BeginPlay()
{
	Super::BeginPlay();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PlayerController) 
    {
    	return;
    }

    // Find CameraActor by tag
    TArray<AActor*> FoundCameras;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("MainCamera"), FoundCameras);

    if (FoundCameras.Num() > 0)
    {
        AActor* CameraActor = FoundCameras[0];
        PlayerController->SetViewTarget(CameraActor);
    }
}

void APongGameMode::FindOrSpawnPaddle(EPaddleType PaddleType) const
{
	UWorld* World = GetWorld();
    if (!World) 
    {
    	return;
    }

    //-- Look for existing paddle of the given type --//
    TActorIterator<APaddle> PaddlesIterator(World);
    for (; PaddlesIterator; ++PaddlesIterator)
    {
        APaddle* Paddle = *PaddlesIterator;
        if (Paddle && Paddle->GetPaddleType() == PaddleType)
        {
			// If Found one already in level
            return;
        }
    }
	// --

    //-- Not found — spawn a new one --//
	FVector SpawnLocation = GetSpawnLocationForPaddleType(PaddleType);

	// Same for both the Paddles(No Rotation)
	FRotator SpawnRotation = FRotator::ZeroRotator;

	// Always Spawn - Optional (Should never happen)
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    APaddle* NewPaddle = World->SpawnActor<APaddle>(APaddle::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
    if (NewPaddle)
    {
        NewPaddle->SetPaddleType(PaddleType);
    }
	//--
}

FVector APongGameMode::GetSpawnLocationForPaddleType(EPaddleType InPaddleType) const
{
    FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);

	APongGameMode* PongGameMode = Cast<APongGameMode>(UGameplayStatics::GetActorOfClass(GetWorld(), APongGameMode::StaticClass()));

	if (!PongGameMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Unable to find Pong Game Mode! Invalid Spawn Location sent as Origin!"));
		return SpawnLocation;
	}

	switch (InPaddleType)
	{
	case EPaddleType::PLAYER_1:
		{
			SpawnLocation = PongGameMode->LeftPaddleSpawnLocation;
		}
		break;

	case EPaddleType::PLAYER_2:
	case EPaddleType::AI:
		{
			SpawnLocation = PongGameMode->RightPaddleSpawnLocation;
		}
		break;

	case EPaddleType::NONE:
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to Get Spawn Location! Provide a valid PaddleType!"));
		}
		break;
	}

	return SpawnLocation;
}
