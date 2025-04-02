// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UStateMachineComponent.generated.h"

class UStateBase;

/**
 * A reusable and extensible state machine component for managing actor states at runtime.
 * 
 * This component handles transitioning between gameplay states derived from UStateBase.
 * It stores references to both the current and previous state, and ticks the current state every frame.
 * 
 * Intended to be attached to actors such as paddles, balls, or other game objects that require state-based behavior.
 *
 * Note: For faster implementation should also work with State Machine using Tags from this video:
 * https://youtu.be/YSOAKnnS8iw?si=bNJ4PlFR0-LobrZD
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PONG3D_API UUStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

    // Holds the previously active state: Starts as NULL
    // PushDown-Automaton will be helpful(using stacks or arrays)
    UPROPERTY()
    UStateBase* PreviousState;

    // Holds the currently active state
    UPROPERTY()
    UStateBase* CurrentState;

public:
    // Default-Constructor
    UUStateMachineComponent();

    /**
     * Initializes the state machine with the given starting state.
     * Should be called once, typically in BeginPlay().
     *
     * @param InitialState The first state the state machine should enter.
     */
    UFUNCTION(BlueprintCallable)
    void InitializeState(UStateBase* InitialState);

    /**
     * Transitions from the current state to a new state.
     * Calls Exit() on the current state and Enter() on the new one.
     *
     * @param NewState The new state to transition into.
     */
    UFUNCTION(BlueprintCallable)
    void ChangeState(UStateBase* NewState);

    /**
     * Returns the currently active state.
     */
    UFUNCTION(BlueprintCallable)
    UStateBase* GetCurrentState() const;

    /**
     * Returns the most recent previous state.
     */
    UFUNCTION(BlueprintCallable)
    UStateBase* GetPreviousState() const;

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
