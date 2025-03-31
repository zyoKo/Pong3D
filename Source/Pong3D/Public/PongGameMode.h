// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameMode.generated.h"

// Forward Declaration Class/Structs
class APaddle;

// Forward Declaration Enums
enum class EPaddleType : uint8;

/**
 * 
 */
UCLASS()
class PONG3D_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	int32 LeftPlayerScore = 0;

	UPROPERTY(VisibleAnywhere)
	int32 RightPlayerScore = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<APaddle> PaddleClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector LeftPaddleSpawnLocation = FVector(-400.0f, 0.0f, 50.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector RightPaddleSpawnLocation = FVector(400.0f, 0.0, 50.0f);

public:
	APongGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

private:
	void FindOrSpawnPaddle(EPaddleType PaddleType) const;

	void ResetBall();
};
