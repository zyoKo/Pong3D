// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleStateIdle.h"

#include "Kismet/GameplayStatics.h"
#include "Pong3D/Paddle.h"

void UPaddleStateIdle::Enter(AActor* Owner, UUStateMachineComponent* StateMachine)
{
	Super::Enter(Owner, StateMachine);

	if (!Owner)
	{
		return;
	}

	APaddle* Paddle = Cast<APaddle>(Owner);
	if (Paddle)
	{
		//Paddle->GetCollider()->SetPhysicsLinearVelocity(FVector::Zero());
	}
}

void UPaddleStateIdle::Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime)
{
	Super::Update(Owner, StateMachine, DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, 
        FString::Printf(TEXT("Current State for %s: PaddleStateIdle!"), *Owner->GetName()));
}

void UPaddleStateIdle::Exit(AActor* Owner, UUStateMachineComponent* StateMachine)
{
	Super::Exit(Owner, StateMachine);


}

UStateBase* UPaddleStateIdle::HandleInput(AActor* Owner, UUStateMachineComponent* StateMachine)
{
	return Super::HandleInput(Owner, StateMachine);
}
