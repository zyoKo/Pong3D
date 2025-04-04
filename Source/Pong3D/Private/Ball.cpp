// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"

// Engine Includes
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"

// Project Includes
#include "Paddle.h"
#include "PongGameMode.h"

// Sets default values
ABall::ABall()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	//-- Initialize the Ball Class with Mesh and Collide --//
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereCollider"));
	RootComponent = BoxCollider;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(BoxCollider);

	// Initialize the Mesh Component
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
	MeshComponent->SetSimulatePhysics(false);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//--

	//-- Initialize the BoxCollider Component --//
	// Physics Properties Override
	BoxCollider->SetSimulatePhysics(true);
	BoxCollider->SetEnableGravity(false);
	BoxCollider->SetLinearDamping(0.0f);
	BoxCollider->SetAngularDamping(0.0f);
	// Lock Ball Movement(not required for Pong)
	BoxCollider->BodyInstance.bLockRotation = true;
	BoxCollider->BodyInstance.bLockYTranslation = true;
	// Enable Hit/Overlap Queries
	BoxCollider->SetNotifyRigidBodyCollision(true);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollider->SetCollisionObjectType(ECC_WorldDynamic);
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Block);
	// Add Delegate Bindings for Component Hit/Overlap
	BoxCollider->OnComponentHit.AddDynamic(this, &ABall::OnComponentHitImpl);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnComponentBeginOverlapImpl);
	//--

	// State Machine logic is disabled(Out of Scope of current Implementation).
	//StateMachine = CreateDefaultSubobject<UUStateMachineComponent>(TEXT("BallStateMachine"));
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	// State Machine logic is disabled(Out of Scope of current Implementation).
	// Start in Idle State
	//StateMachine->InitializeState(NewObject<UBallStateIdle>(this));

	ResetBall();
}

void ABall::LaunchBall()
{
	LaunchInRandomDirection();
}

UBoxComponent* ABall::GetBoxCollider() const
{
	return BoxCollider;
}

void ABall::OnComponentHitImpl(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == this) 
	{
		return;
	}

    // Check if it's a paddle(Debug)
    if (OtherActor->IsA(APaddle::StaticClass()))
    {
        UE_LOG(LogTemp, Log, TEXT("Ball hit a paddle!"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Ball hit something else: %s"), *OtherActor->GetName());
    }
}

/**
 * Add score to the player based on if the left or right trigger hit by the ball.
 */
void ABall::OnComponentBeginOverlapImpl(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Ball Begin Overlap : %s"), *OtherActor->GetName());

	APongGameMode* PongGameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (LeftPlayerTriggerBox && OtherActor == LeftPlayerTriggerBox && PongGameMode)
	{
		++PongGameMode->RightPlayerScore;
		PongGameMode->PaddleThatScoredLastPoint = EPaddleType::PLAYER_2;

		// State Machine logic is disabled(Out of Scope of current Implementation).
		//StateMachine->ChangeState(NewObject<UBallStateIdle>(this));

		ResetBall();
	}

	if (RightPlayerTriggerBox && OtherActor == RightPlayerTriggerBox && PongGameMode)
	{
		++PongGameMode->LeftPlayerScore;
		PongGameMode->PaddleThatScoredLastPoint = EPaddleType::PLAYER_1;

		// State Machine logic is disabled(Out of Scope of current Implementation).
		//StateMachine->ChangeState(NewObject<UBallStateIdle>(this));

		ResetBall();
	}
}

void ABall::ResetBall()
{
	SetActorLocation(FVector::ZeroVector);

	BoxCollider->SetPhysicsLinearVelocity(FVector::ZeroVector);
}

void ABall::LaunchInRandomDirection()
{
	// Get Pong Game Mode Base
	auto* GameMode = Cast<APongGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode)
	{
		UE_LOG(LogTemp, Log, TEXT("Pong Game Mode not assigned for this World!"));
		return;
	}

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
    LaunchVelocity = LaunchDirection * MoveSpeed;
    BoxCollider->SetPhysicsLinearVelocity(LaunchVelocity);
}
