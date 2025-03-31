// Fill out your copyright notice in the Description page of Project Settings.


#include "UStateMachineComponent.h"

#include "StateBase.h"

// Sets default values for this component's properties
UUStateMachineComponent::UUStateMachineComponent()
	: PreviousState(nullptr)
	, CurrentState(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UUStateMachineComponent::InitializeState(UStateBase* InitialState)
{
	if (!InitialState)
	{
		return;
	}

	CurrentState = InitialState;
	auto* Owner = GetOwner();
	CurrentState->Enter(Owner, this);
}

void UUStateMachineComponent::ChangeState(UStateBase* NewState)
{
	if (!NewState || NewState == CurrentState) 
	{
		return;
	}

	CurrentState->Exit(GetOwner(), this);
	PreviousState = CurrentState;
	CurrentState = NewState;
	CurrentState->Enter(GetOwner(), this);
}

UStateBase* UUStateMachineComponent::GetCurrentState() const
{
	return CurrentState;
}

UStateBase* UUStateMachineComponent::GetPreviousState() const
{
	return PreviousState;
}

// Called every frame
void UUStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (CurrentState)
    {
        UStateBase* NextState = CurrentState->HandleInput(GetOwner(), this);
        if (NextState && NextState != CurrentState)
        {
            ChangeState(NextState);
        }
        CurrentState->Update(GetOwner(), this, DeltaTime);
    }
}

