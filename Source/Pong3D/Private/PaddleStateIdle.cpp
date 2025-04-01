// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleStateIdle.h"
#include "Pong3D/Paddle.h"

void UPaddleStateIdle::Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime)
{
	Super::Update(Owner, StateMachine, DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, 
        FString::Printf(TEXT("Current State for %s: PaddleStateIdle!"), *Owner->GetName()));

	APaddle* Paddle = Cast<APaddle>(Owner);
	UPrimitiveComponent* PhysicsComponent = Paddle->GetCollider();
	if (PhysicsComponent)
	{
		FVector Velocity = PhysicsComponent->GetPhysicsLinearVelocity();

		if (!Velocity.IsNearlyZero())
		{
		    const float TimeToStop = 0.1f;
		    FVector Acceleration = -Velocity / TimeToStop;
		
		    // Apply acceleration each tick (Frame-dependent)
		    PhysicsComponent->AddForce(Acceleration * PhysicsComponent->GetMass()); // use AddForce for realistic mass
		}
	}
}
