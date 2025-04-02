// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaddleStateBase.h"
#include "PaddleStateHit.generated.h"

/**
 * Paddle State Hit State For the APaddle Class
 */
UCLASS()
class PONG3D_API UPaddleStateHit : public UPaddleStateBase
{
	GENERATED_BODY()

public:
	virtual void Enter(AActor* Owner, UUStateMachineComponent* StateMachine) override;

protected:
	void ReflectBallFromPaddle(AActor* PaddleActor, UUStateMachineComponent* StateMachine) const;
};
