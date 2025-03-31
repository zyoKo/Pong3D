// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpectatorPawn.h"

#include "PongPlayerController.h"
#include "Pong3D/Ball.h"
#include "Pong3D/Paddle.h"

APongGameMode::APongGameMode()
{
	// Set the custom player controller
    PlayerControllerClass = APongPlayerController::StaticClass();

    // Set default pawn to none, since we don't want the player to possess anything
    DefaultPawnClass = ASpectatorPawn::StaticClass();
}

void APongGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

    // Spawn or find both Paddles
	FindOrSpawnPaddle(EPaddleType::PLAYER_1);
	FindOrSpawnPaddle(EPaddleType::PLAYER_2);
}

void APongGameMode::FindOrSpawnPaddle(EPaddleType PaddleType) const
{
	UWorld* World = GetWorld();
    if (!World) 
    {
    	return;
    }

    //-- Look for existing paddle of the given type --//
    for (TActorIterator<APaddle> It(World); It; ++It)
    {
        APaddle* Paddle = *It;
        if (Paddle && Paddle->GetPaddleType() == PaddleType)
        {
            return;  // Found one already in level
        }
    }
	// --

    //-- Not found — spawn a new one --//

	// Find Spawn Location based on PaddleType
	FVector SpawnLocation = APaddle::GetSpawnLocationForPaddleType(PaddleType);

	// Same for both the Paddles(No Rotation)
	FRotator SpawnRotation = FRotator::ZeroRotator;

	// Always Spawn - Optional (Should never happen)
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    APaddle* NewPaddle = World->SpawnActor<APaddle>(APaddle::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
    if (NewPaddle)
    {
        NewPaddle->SetPaddleType(PaddleType);  // Optional if you want to assign type after spawn
    }
}

void APongGameMode::ResetBall()
{
	ABall* ball = Cast<ABall>(UGameplayStatics::GetActorOfClass(this, ABall::StaticClass()));
	if (ball)
	{
		ball->ResetBall();
	}
}
