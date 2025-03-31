// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaddleStateBase.h"
#include "PaddleStateIdle.generated.h"

/**
 * 
 */
UCLASS()
class PONG3D_API UPaddleStateIdle : public UPaddleStateBase
{
	GENERATED_BODY()

public:
	virtual void Enter(AActor* Owner, UUStateMachineComponent* StateMachine) override;

	virtual void Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime) override;

	virtual void Exit(AActor* Owner, UUStateMachineComponent* StateMachine) override;

	virtual UStateBase* HandleInput(AActor* Owner, UUStateMachineComponent* StateMachine) override;
};
