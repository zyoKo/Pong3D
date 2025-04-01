// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallStateBase.h"
#include "BallStateIdle.generated.h"

/**
 * 
 */
UCLASS()
class PONG3D_API UBallStateIdle : public UBallStateBase
{
	GENERATED_BODY()

public:
	virtual void Enter(AActor* Owner, UUStateMachineComponent* StateMachine) override;

	virtual void Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime) override;

protected:
	void ResetBall(AActor* Owner);

	void LaunchInRandomDirection(AActor* Owner, UUStateMachineComponent* StateMachine);
};
