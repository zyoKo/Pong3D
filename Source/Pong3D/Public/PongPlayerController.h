// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongPlayerController.generated.h"

class APaddle;

/**
 * Custom player controller for Pong3D.
 * Responsible for:
 *  - Binding player input for paddle movement and ball launching
 *  - Tracking references to left and right paddles
 *  - Forwarding input values to the appropriate paddle instances
 *  
 * This controller supports two players on the same machine, with independent input mappings for each paddle.
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
    /**
     * Called when the game starts or when the player controller is spawned.
     * Finds and assigns references to the left and right paddles based on their PaddleType.
     */
    virtual void BeginPlay() override;

    /**
     * Binds player input actions and axes to controller functions.
     * - Binds movement axes for both paddles.
     * - Binds the ball launch action if the ball is present in the world.
     */
    virtual void SetupInputComponent() override;

protected:
    /**
     * Called every frame when the left paddle movement input axis is updated.
     * Forwards input value to the left paddle for movement.
     *
     * @param AxisValue Input value ranging from -1 to 1, depending on player input.
     */
    void MoveLeftPaddle(float AxisValue);

    /**
     * Called every frame when the right paddle movement input axis is updated.
     * Forwards input value to the right paddle for movement.
     *
     * @param AxisValue Input value ranging from -1 to 1, depending on player input.
     */
    void MoveRightPaddle(float AxisValue);
};
