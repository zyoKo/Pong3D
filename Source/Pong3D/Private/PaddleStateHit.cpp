// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleStateHit.h"

#include "UStateMachineComponent.h"
#include "Kismet/GameplayStatics.h"

#include "PaddleStateIdle.h"
#include "PaddleStateMoving.h"
#include "Pong3D/Ball.h"
#include "Pong3D/Paddle.h"

void UPaddleStateHit::Enter(AActor* Owner, UUStateMachineComponent* StateMachine)
{
	Super::Enter(Owner, StateMachine);

    GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, 
        FString::Printf(TEXT("Current State for %s: PaddleStateHit!"), *Owner->GetName()));

	UE_LOG(LogTemp, Log, TEXT("%s entered HIT state"), *Owner->GetName());

    if (Owner)
    {
        ReflectBallFromPaddle(Owner, StateMachine);
    }

    // Immediately return to Idle
    TransitionState(Owner, StateMachine, EPaddleState::IDLE);
}

void UPaddleStateHit::ReflectBallFromPaddle(AActor* PaddleActor, UUStateMachineComponent* StateMachine) const
{
    APaddle* Paddle = Cast<APaddle>(PaddleActor);
    if (!Paddle) 
    {
    	return;
    }

    ABall* Ball = Cast<ABall>(UGameplayStatics::GetActorOfClass(Paddle->GetWorld(), ABall::StaticClass()));
    if (!Ball) 
    {
    	return;
    }

    FVector BallVelocity = Ball->GetVelocity();

    // Reverse X-direction
    BallVelocity.X *= -1;

    // Add vertical influence based on last paddle movement input
    // Check last state, if Idle reflect Normally but if Moving then adjust influence strength

    bool isPreviousStateMovingState = dynamic_cast<UPaddleStateMoving*>(StateMachine->GetPreviousState()) != nullptr;
	if ( isPreviousStateMovingState )
    {
    	float PaddleInput = Paddle->GetMovementAxisValue();
        BallVelocity.Z += PaddleInput * 300.0f; // Adjust influence strength as needed
        auto* BallStaticMeshComponent = Ball->GetComponentByClass<UStaticMeshComponent>();
		BallStaticMeshComponent->SetPhysicsLinearVelocity(BallVelocity); // Assumes ABall has SetVelocity(FVector)

        UE_LOG(LogTemp, Log, TEXT("Ball reflected: new velocity = %s"), *BallVelocity.ToString());

        TransitionState(PaddleActor, StateMachine, EPaddleState::MOVING);
    }
}
