// Fill out your copyright notice in the Description page of Project Settings.


#include "BallStateBase.h"

#include "BallStateHit.h"
#include "BallStateIdle.h"
#include "BallStateMoving.h"
#include "UStateMachineComponent.h"

void UBallStateBase::Enter(AActor* Owner, UUStateMachineComponent* StateMachine)
{ }

void UBallStateBase::Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime)
{ }

void UBallStateBase::Exit(AActor* Owner, UUStateMachineComponent* StateMachine)
{ }

UStateBase* UBallStateBase::HandleInput(AActor* Owner, UUStateMachineComponent* StateMachine)
{
	return nullptr;
}

void UBallStateBase::TransitionState(AActor* Owner, UUStateMachineComponent* StateMachine, EBallState PaddleState) const
{
	UStateBase* NewStateInstance = nullptr;

    switch (PaddleState)
    {
    case EBallState::IDLE:
        NewStateInstance = NewObject<UBallStateIdle>(Owner);
        break;
    case EBallState::MOVING:
        NewStateInstance = NewObject<UBallStateMoving>(Owner);
        break;
    case EBallState::HIT:
        NewStateInstance = NewObject<UBallStateHit>(Owner);
        break;
    }

    if (NewStateInstance)
    {
        StateMachine->ChangeState(NewStateInstance);
    }
}
