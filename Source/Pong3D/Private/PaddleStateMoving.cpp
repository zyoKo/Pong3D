// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleStateMoving.h"

#include "Kismet/GameplayStatics.h"
#include "Pong3D/Paddle.h"

void UPaddleStateMoving::Enter(AActor* Owner, UUStateMachineComponent* StateMachine)
{
	Super::Enter(Owner, StateMachine);


}

void UPaddleStateMoving::Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime)
{
	Super::Update(Owner, StateMachine, DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, 
        FString::Printf(TEXT("Current State for %s: PaddleStateMoving!"), *Owner->GetName()));

	APaddle* Paddle = nullptr;
	if (Owner)
	{
		Paddle = Cast<APaddle>(Owner);
	}

	if (!Paddle)
	{
		return;
	}

	// Get physics component (Make sure it's Root)
	UPrimitiveComponent* PhysicsComp = Paddle->GetCollider();
	if (!PhysicsComp || !PhysicsComp->IsSimulatingPhysics()) 
	{
		// Maintain constant velocity while clamping position manually
		FVector NewLocation = Paddle->GetActorLocation();
		NewLocation.Z += Paddle->GetMovementAxisValue() * Paddle->GetMoveSpeed() * DeltaTime;
		Paddle->SetActorLocation(NewLocation);
		
		// Bounds Check
		NewLocation.Z = FMath::Clamp(NewLocation.Z, -400.0f, 300.0f);

		return;
	}

	// Compute new velocity in Z
	float Input = Paddle->GetMovementAxisValue();
	float Speed = Paddle->GetMoveSpeed();
	FVector Velocity = FVector(0.0f, 0.0f, Input * Speed);

	// Apply velocity
	PhysicsComp->SetPhysicsLinearVelocity(Velocity, false);
}

void UPaddleStateMoving::Exit(AActor* Owner, UUStateMachineComponent* StateMachine)
{
	Super::Exit(Owner, StateMachine);


}

UStateBase* UPaddleStateMoving::HandleInput(AActor* Owner, UUStateMachineComponent* StateMachine)
{
	return Super::HandleInput(Owner, StateMachine);
}
