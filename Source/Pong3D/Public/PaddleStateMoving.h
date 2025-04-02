// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaddleStateBase.h"
#include "PaddleStateMoving.generated.h"

/**
 * Holds the Paddle Movement Logic.
 */
UCLASS()
class PONG3D_API UPaddleStateMoving : public UPaddleStateBase
{
	GENERATED_BODY()

public:
	virtual void Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime) override;
};
