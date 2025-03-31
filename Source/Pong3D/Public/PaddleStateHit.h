// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaddleStateBase.h"
#include "PaddleStateHit.generated.h"

/**
 * 
 */
UCLASS()
class PONG3D_API UPaddleStateHit : public UPaddleStateBase
{
	GENERATED_BODY()

	friend class APaddle;

public:
	virtual void Enter(AActor* Owner, UUStateMachineComponent* StateMachine) override;

protected:
	void ReflectBallFromPaddle(AActor* PaddleActor, UUStateMachineComponent* StateMachine) const;
};
