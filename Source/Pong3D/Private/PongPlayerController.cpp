// Fill out your copyright notice in the Description page of Project Settings.


#include "PongPlayerController.h"

#include "EngineUtils.h"

#include "PaddleType.h"
#include "Pong3D/Paddle.h"

void APongPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Find paddles in the level by their PaddleType
    for (TActorIterator<APaddle> It(GetWorld()); It; ++It)
    {
        APaddle* Paddle = *It;
        if (!Paddle) continue;

        if (Paddle->GetPaddleType() == EPaddleType::PLAYER_1)
        {
            LeftPaddle = Paddle;
        }
        else if (Paddle->GetPaddleType() == EPaddleType::PLAYER_2)
        {
            RightPaddle = Paddle;
        }
    }
}

void APongPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Simple to use just one controller for local gameplay
    InputComponent->BindAxis("MoveLeftPaddle", this, &APongPlayerController::MoveLeftPaddle);
    InputComponent->BindAxis("MoveRightPaddle", this, &APongPlayerController::MoveRightPaddle);
}

void APongPlayerController::MoveLeftPaddle(float AxisValue)
{
    LeftPaddle->Move(AxisValue);
}

void APongPlayerController::MoveRightPaddle(float AxisValue)
{
    RightPaddle->Move(AxisValue);
}