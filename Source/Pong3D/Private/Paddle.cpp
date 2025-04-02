// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"

#include "Ball.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Constants.h"
#include "PaddleStateHit.h"
#include "UStateMachineComponent.h"
#include "PaddleStateIdle.h"
#include "PaddleStateMoving.h"
#include "PaddleType.h"

// Sets default values
APaddle::APaddle()
	: PaddleType(EPaddleType::NONE)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//-- Initialize the Ball Class with Mesh and Collide --//
	// Add Box Collider (Handles Physics and Collision Queries)
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;
	// Add Mesh Component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(BoxCollider);

	//-- Setup Mesh Component --//
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(PaddleConstants::CUBE_ASSET);
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
	MeshComponent->SetNotifyRigidBodyCollision(false);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//--

	//-- Setup BoxCollider Component --//
	BoxCollider->SetSimulatePhysics(true);
	BoxCollider->SetEnableGravity(false);
	// ...
	BoxCollider->BodyInstance.bLockXTranslation = true;
	BoxCollider->BodyInstance.bLockYTranslation = true;
	BoxCollider->BodyInstance.bLockXRotation = true;
	BoxCollider->BodyInstance.bLockYRotation = true;
	BoxCollider->BodyInstance.bLockZRotation = true;
	// ...
	BoxCollider->SetNotifyRigidBodyCollision(true);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollider->SetCollisionObjectType(ECC_WorldDynamic);
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Block);
	// ...
	BoxCollider->OnComponentHit.AddDynamic(this, &APaddle::OnComponentHitImpl);
	//--

	//-- Create the StateMachine Component for the paddle --//
	StateMachine = CreateDefaultSubobject<UUStateMachineComponent>(TEXT("StateMachineComponent"));
	//--
}

float APaddle::GetMovementAxisValue() const
{
	return MovementAxisValue;
}

float APaddle::GetMoveSpeed() const
{
	return MoveSpeed;
}

UPrimitiveComponent* APaddle::GetCollider() const
{
	return BoxCollider;
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();

	//-- Initialize the StateMachine Component --//
	// Start in Idle State
    StateMachine->InitializeState(NewObject<UPaddleStateIdle>(this));
	//--
}

void APaddle::Move(float AxisValue)
{
	// Set Last Input Direction Ball Interaction
	MovementAxisValue = AxisValue;

	if (FMath::Abs(AxisValue) > 0.1f) // Avoid small floating point movements
    {
		// Change state to Moving
		StateMachine->ChangeState(NewObject<UPaddleStateMoving>(this));

		return;
    }

	StateMachine->ChangeState(NewObject<UPaddleStateIdle>(this));
}

EPaddleType APaddle::GetPaddleType() const
{
	return PaddleType;
}

void APaddle::SetPaddleType(EPaddleType InPaddleType)
{
	PaddleType = InPaddleType;
}

void APaddle::OnComponentHitImpl(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == this) 
	{
		return;
	}

    // Check if it's the Ball
    if (OtherActor->IsA(ABall::StaticClass()))
    {
        UE_LOG(LogTemp, Log, TEXT("Ball hit a paddle!"));

		//-- If yes, use the Hit Logic in PaddleStateHit
        if (ABall* Ball = Cast<ABall>(OtherActor))
        {
            StateMachine->ChangeState(NewObject<UPaddleStateHit>(this));
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Paddle hit something else: %s"), *OtherActor->GetName());
    }
}

void APaddle::PlayBounceSoundAtLocation() const
{
	if (!BounceSound)
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to play Sounds: %s"), *BounceSound->GetName());
		return;
	}

	//-- Adding a delay between playing sounds to avoid Sound Spam --//
	float CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime - LastSoundTime >= SoundCooldown)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BounceSound, GetActorLocation());
	}

	LastSoundTime = CurrentTime;
	//--
}
