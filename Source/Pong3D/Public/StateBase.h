// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.generated.h"

class UUStateMachineComponent;

/**
 * Abstract base class for implementing gameplay states using a custom state machine.
 * 
 * Derived classes must implement the Enter, Exit, Update, and HandleInput methods to define
 * specific state behavior. This class is not meant to be instantiated directly.
 * 
 * Designed to work with actors (Pawn, Character, etc.) using a UUStateMachineComponent
 * to manage transitions between gameplay states.
 *
 * Note: Currently, HandleInput Serves no purpose and can be removed.
 */
UCLASS(Abstract)
class PONG3D_API UStateBase : public UObject
{
	GENERATED_BODY()
	
public:
	/**
	 * Called when the state is first entered.
	 *
	 * @param Owner The actor that owns the state machine.
	 * @param StateMachine The state machine component managing this state.
	 */
    virtual void Enter(AActor* Owner, UUStateMachineComponent* StateMachine)
	PURE_VIRTUAL(UStateBase::Enter, );

	/**
	 * Called when the state is about to exit.
	 *
	 * @param Owner The actor that owns the state machine.
	 * @param StateMachine The state machine component managing this state.
	 */
    virtual void Exit(AActor* Owner, UUStateMachineComponent* StateMachine)
	PURE_VIRTUAL(UStateBase::Exit, );

	/**
	 * Called every frame while this state is active.
	 *
	 * @param Owner The actor that owns the state machine.
	 * @param StateMachine The state machine component managing this state.
	 * @param DeltaTime Time since last frame.
	 */
    virtual void Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime)
	PURE_VIRTUAL(UStateBase::Update, );

	/**
	 * Handles input or state-specific conditions to determine if a transition is needed.
	 * (Note: Currently, serves no purpose in the game.)
	 * 
	 * @param Owner The actor that owns the state machine.
	 * @param StateMachine The state machine component managing this state.
	 * @return A new state to transition to, or nullptr to stay in current state.
	 */
    virtual UStateBase* HandleInput(AActor* Owner, UUStateMachineComponent* StateMachine)
	PURE_VIRTUAL(UStateBase::HandleInput, return nullptr; );
};
