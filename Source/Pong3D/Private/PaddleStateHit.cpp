// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleStateHit.h"

#include "UStateMachineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

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
    if (!Paddle) return;

    ABall* Ball = Cast<ABall>(UGameplayStatics::GetActorOfClass(Paddle->GetWorld(), ABall::StaticClass()));
    if (!Ball) return;

    float PaddleInput = Paddle->GetMovementAxisValue();

    // Determine X direction: if paddle is on left side, go right (+X), else left (-X)
    float XDirection = Paddle->GetActorLocation().X < 0 ? 1.0f : -1.0f;

    FVector ReflectDirection = FVector(XDirection, 0.0f, PaddleInput * 0.4f); // Small Z influence
    ReflectDirection = ReflectDirection.GetSafeNormal();

    float BallSpeed = 1000.0f; //Ball->GetInitialSpeed(); // You must track this value somewhere
    FVector NewVelocity = ReflectDirection * BallSpeed;

    UBoxComponent* BallComponent = Cast<UBoxComponent>(Ball->GetComponentByClass(UBoxComponent::StaticClass()));
    if (BallComponent)
    {
        BallComponent->SetPhysicsLinearVelocity(NewVelocity, false);
    }

    UE_LOG(LogTemp, Log, TEXT("Ball reflected with stable X direction. Velocity: %s"), *NewVelocity.ToString());

    TransitionState(PaddleActor, StateMachine, EPaddleState::MOVING);
}
