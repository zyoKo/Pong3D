// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleStateBase.h"

#include "PaddleStateHit.h"
#include "PaddleStateIdle.h"
#include "PaddleStateMoving.h"
#include "UStateMachineComponent.h"

void UPaddleStateBase::Enter(AActor* Owner, UUStateMachineComponent* StateMachine)
{

}

void UPaddleStateBase::Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime)
{

}

void UPaddleStateBase::Exit(AActor* Owner, UUStateMachineComponent* StateMachine)
{

}

UStateBase* UPaddleStateBase::HandleInput(AActor* Owner, UUStateMachineComponent* StateMachine)
{
	return nullptr;
}

void UPaddleStateBase::TransitionState(AActor* Owner, UUStateMachineComponent* StateMachine, EPaddleState PaddleState) const
{
    UStateBase* NewStateInstance = nullptr;

    switch (PaddleState)
    {
    case EPaddleState::IDLE:
        NewStateInstance = NewObject<UPaddleStateIdle>(Owner);
        break;
    case EPaddleState::MOVING:
        NewStateInstance = NewObject<UPaddleStateMoving>(Owner);
        break;
    case EPaddleState::HIT:
        NewStateInstance = NewObject<UPaddleStateHit>(Owner);
        break;
    case EPaddleState::MISS:
        //NewStateInstance = NewObject<UPaddleMissedState>(Owner);
        break;
    case EPaddleState::GAME_OVER:
        //NewStateInstance = NewObject<UPaddleGameOverState>(Owner);
        break;
    default:
        break;
    }

    if (NewStateInstance)
    {
        StateMachine->ChangeState(NewStateInstance);
    }
}
