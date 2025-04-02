// Fill out your copyright notice in the Description page of Project Settings.


#include "PongPlayerController.h"

// Engine Includes
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Project Includes
#include "PaddleType.h"
#include "Ball.h"
#include "Paddle.h"

void APongPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Find paddles in the level by their PaddleType
    for (TActorIterator<APaddle> PaddleIterator(GetWorld()); PaddleIterator; ++PaddleIterator)
    {
        APaddle* Paddle = *PaddleIterator;
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

    ABall* Ball = Cast<ABall>(UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass()));

    // Bind Axis
    InputComponent->BindAxis("MoveLeftPaddle", this, &APongPlayerController::MoveLeftPaddle);
    InputComponent->BindAxis("MoveRightPaddle", this, &APongPlayerController::MoveRightPaddle);

    // Bind Actions
    if (Ball)
    {
		InputComponent->BindAction("LaunchBall", IE_Pressed, Ball, &ABall::LaunchBall);
    }
}

void APongPlayerController::MoveLeftPaddle(float AxisValue)
{
    LeftPaddle->Move(AxisValue);
}

void APongPlayerController::MoveRightPaddle(float AxisValue)
{
    RightPaddle->Move(AxisValue);
}
