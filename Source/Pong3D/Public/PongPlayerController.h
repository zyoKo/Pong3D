// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongPlayerController.generated.h"

class APaddle;

/**
 * 
 */
UCLASS()
class PONG3D_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()

    UPROPERTY()
    APaddle* LeftPaddle;

    UPROPERTY()
    APaddle* RightPaddle;

    UPROPERTY(EditAnywhere, Category = "Paddle")
    float PaddleSpeed = 500.0f;

public:
    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;

protected:
    void MoveLeftPaddle(float AxisValue);

    void MoveRightPaddle(float AxisValue);
};
