// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.generated.h"

class UUStateMachineComponent;

/**
 * 
 */
UCLASS()
class PONG3D_API UStateBase : public UObject
{
	GENERATED_BODY()
	
public:
    virtual void Enter(AActor* Owner, UUStateMachineComponent* StateMachine) PURE_VIRTUAL(UStateBase::Enter);

    virtual void Exit(AActor* Owner, UUStateMachineComponent* StateMachine) PURE_VIRTUAL(UStateBase::Exit);

    virtual void Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime) PURE_VIRTUAL(UStateBase::Update);

    virtual UStateBase* HandleInput(AActor* Owner, UUStateMachineComponent* StateMachine) PURE_VIRTUAL(UStateBase::HandleInput, return nullptr;);
};
