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
 * 
 */
UCLASS()
class PONG3D_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<APaddle> PaddleClass;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector LeftPaddleSpawnLocation = FVector(-900.0f, 0.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector RightPaddleSpawnLocation = FVector(900.0f, 0.0, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	int32 LeftPlayerScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	int32 RightPlayerScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsGameOver = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPaddleType PaddleThatScoredLastPoint = EPaddleType::NONE;

public:
	APongGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

protected:
	virtual void BeginPlay() override;

private:
	void FindOrSpawnPaddle(EPaddleType PaddleType) const;

	FVector GetSpawnLocationForPaddleType(EPaddleType InPaddleType) const;
};
