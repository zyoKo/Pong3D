// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaddleType.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameMode.generated.h"

// Forward Declaration Class/Structs
class APaddle;

// Forward Declaration Enums
enum class EPaddleType : uint8;

/**
 * APongGameMode handles the main game loop logic for Pong3D.
 * 
 * Responsibilities:
 * - Spawns or finds paddles and ball at game start
 * - Tracks player scores and scoring paddle
 * - Defines spawn locations for key game elements
 */
UCLASS()
class PONG3D_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()

	// The class type of the paddle to spawn at game start
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<APaddle> PaddleClass;

public:
	// World location to spawn the left player's paddle
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector LeftPaddleSpawnLocation = FVector(-900.0f, 0.0f, 0.0f);

	// World location to spawn the right player's paddle
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector RightPaddleSpawnLocation = FVector(900.0f, 0.0, 0.0f);

	// World location to spawn the ball at the start of the game or after scoring 
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector BallSpawnLocation = FVector(0.0f, 0.0f, 0.0f);

	// The current score of the left player
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	int32 LeftPlayerScore = 0;

	// The current score of the right player
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	int32 RightPlayerScore = 0;

	// Stores which paddle scored the last point
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPaddleType PaddleThatScoredLastPoint = EPaddleType::NONE;

public:
	// Constructor: Sets default values and configures default pawn class
	APongGameMode();

	/**
	 * Called when the game instance initializes this game mode.
	 * Used to parse map/game options before BeginPlay.
	 */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

protected:
	/**
	 * Called when the game begins play (after all actors have been spawned).
	 * Handles initial spawning or lookup of paddles and ball.
	 */
	virtual void BeginPlay() override;

private:
	/**
	 * Finds an existing paddle with the given PaddleType in the level,
	 * or spawns one using PaddleClass at the correct location.
	 * 
	 * @param PaddleType The player side to find or spawn (PLAYER_1 or PLAYER_2)
	 */
	void FindOrSpawnPaddle(EPaddleType PaddleType) const;

	/**
	 * Finds an existing ball in the level or spawns one at BallSpawnLocation.
	 */
	void FindOrSpawnBall() const;

	/**
	 * Returns the correct world location to spawn a paddle based on its PaddleType.
	 *
	 * @param InPaddleType The paddle side (PLAYER_1 or PLAYER_2)
	 * @return Spawn location as FVector
	 */
	FVector GetSpawnLocationForPaddleType(EPaddleType InPaddleType) const;
};
