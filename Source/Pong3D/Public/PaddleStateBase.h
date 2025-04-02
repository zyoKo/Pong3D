// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "PaddleStateBase.generated.h"

/**
 * Paddle State Base State For the APaddle Class.
 *
 * This Class is used to Derive the Actual States Implementations.
 */
UCLASS()
class PONG3D_API UPaddleStateBase : public UStateBase
{
	GENERATED_BODY()

public:
	virtual void Enter(AActor* Owner, UUStateMachineComponent* StateMachine) override;

	virtual void Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime) override;

	virtual void Exit(AActor* Owner, UUStateMachineComponent* StateMachine) override;

	virtual UStateBase* HandleInput(AActor* Owner, UUStateMachineComponent* StateMachine) override;

protected:
	// Internal Enum (Maybe Exposed to Blueprints Later?)
	enum class EPaddleState
	{
		IDLE,
		MOVING,
		HIT,
		MISS,		/* TODO: Not used atm */
		GAME_OVER   /* TODO: Not used atm */
	};

	void TransitionState(AActor* Owner, UUStateMachineComponent* StateMachine, EPaddleState PaddleState) const;
};
