// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaddleStateBase.h"
#include "PaddleStateIdle.generated.h"

/**
 * Paddle State Idle State For the APaddle Class
 */
UCLASS()
class PONG3D_API UPaddleStateIdle : public UPaddleStateBase
{
	GENERATED_BODY()

public:
	virtual void Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime) override;
};
