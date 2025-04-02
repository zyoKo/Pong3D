// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"

// Engine Includes
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Project Includes
#include "Ball.h"
#include "Paddle.h"
#include "PongPlayerController.h"

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

	//FindOrSpawnBall();
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
	//--

    //-- Not found — spawn a new one --//
	FVector SpawnLocation = GetSpawnLocationForPaddleType(PaddleType);

	// Same for both the Paddles(No Rotation)
	FRotator SpawnRotation = FRotator::ZeroRotator;

	// Always Spawn - Optional (Should never happen)
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APaddle* NewPaddle;
	if (!PaddleClass)
	{
		NewPaddle = World->SpawnActor<APaddle>(APaddle::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	}
	else
	{
		NewPaddle = World->SpawnActor<APaddle>(PaddleClass, SpawnLocation, SpawnRotation, SpawnParams);
	}

    if (!NewPaddle)
    {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Create Paddle Class!"));
		return;
    }
	NewPaddle->SetPaddleType(PaddleType);
	//--
}

void APongGameMode::FindOrSpawnBall() const
{
	UWorld* World = GetWorld();
    if (!World) 
    {
    	return;
    }

    //-- Look for existing paddle of the given type --//
	TArray<AActor*> BallArray;
    UGameplayStatics::GetAllActorsOfClass(World, ABall::StaticClass(), BallArray);
	SIZE_T TotalBallActorsInScene = BallArray.Num();
	if (TotalBallActorsInScene > 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Multiple Balls found in the Scene!"));

		// Removing All Other Balls except 1
		for (SIZE_T BallActorIndex = 1; BallActorIndex < TotalBallActorsInScene; ++BallActorIndex)
		{
			BallArray[BallActorIndex]->Destroy();
		}

		if (ABall* Ball = Cast<ABall>(BallArray[0]))
		{
			Ball->SetActorLocation(BallSpawnLocation);
		}

		return;
	} else if (TotalBallActorsInScene == 1)
	{
		if (ABall* Ball = Cast<ABall>(BallArray[0]))
		{
			Ball->SetActorLocation(BallSpawnLocation);
		}

		return;
	}
	//--

	//-- If we can't find Ball then Spawn --//
	// Always Spawn - Optional (Should never happen)
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ABall* NewBall = World->SpawnActor<ABall>(ABall::StaticClass(), BallSpawnLocation, FRotator::ZeroRotator, SpawnParams);
	if (!NewBall)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Create Ball Class!"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("New Ball Spawned in the Scene!"));
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
