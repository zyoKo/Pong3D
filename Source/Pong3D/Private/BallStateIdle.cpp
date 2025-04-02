// Fill out your copyright notice in the Description page of Project Settings.


#include "BallStateIdle.h"

#include "PongGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Ball.h"

void UBallStateIdle::Enter(AActor* Owner, UUStateMachineComponent* StateMachine)
{
	Super::Enter(Owner, StateMachine);

	ResetBall(Owner);
}

void UBallStateIdle::Update(AActor* Owner, UUStateMachineComponent* StateMachine, float DeltaTime)
{
	Super::Update(Owner, StateMachine, DeltaTime);

	if (ABall* Ball = Cast<ABall>(Owner))
	{
		LaunchInRandomDirection(Owner, StateMachine);

		TransitionState(Owner, StateMachine, EBallState::MOVING);
	}
}

void UBallStateIdle::ResetBall(AActor* Owner)
{
	if (ABall* Ball = Cast<ABall>(Owner))
	{
		// Reset Ball to Origin
		Ball->SetActorLocation(FVector::ZeroVector);

		UBoxComponent* BoxCollider = Ball->GetBoxCollider();
		BoxCollider->SetPhysicsLinearVelocity(FVector::ZeroVector);
	}
}

void UBallStateIdle::LaunchInRandomDirection(AActor* Owner, UUStateMachineComponent* StateMachine)
{
	// Get Pong Game Mode Base
	auto* GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Pong Game Mode not assigned for this World!"));
		return;
	}

	// Cast to Ball
	auto* Ball = Cast<ABall>(Owner);
	if (!Ball)
	{
		return;
	}

	// Get Box Collider
	UBoxComponent* BoxCollider = Ball->GetBoxCollider();

	float MinZAngle = -20.0f;
    float MaxZAngle =  20.0f;

    float ZOffset = FMath::RandRange(MinZAngle, MaxZAngle);

    // Choose a direction along the X axis (left or right)
    float XDirection;
	switch (GameMode->PaddleThatScoredLastPoint)
	{
	case EPaddleType::PLAYER_1:
		XDirection = 1.0f;
		break;

	case EPaddleType::PLAYER_2:
	case EPaddleType::AI:
		XDirection = -1.0f;
		break;

	default:
	case EPaddleType::NONE:
		XDirection = FMath::RandBool() ? 1.0f : -1.0f;
		break;
	}

	// Launch Ball
    FVector LaunchDirection = FVector(XDirection, 0.f, FMath::Tan(FMath::DegreesToRadians(ZOffset)));
    LaunchDirection = LaunchDirection.GetSafeNormal();
    Ball->LaunchVelocity = LaunchDirection * Ball->MoveSpeed;
    BoxCollider->SetPhysicsLinearVelocity(Ball->LaunchVelocity);
}
