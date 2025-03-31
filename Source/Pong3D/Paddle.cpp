// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Constants.h"
#include "UStateMachineComponent.h"
#include "PaddleStateIdle.h"
#include "PaddleStateMoving.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APaddle::APaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

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

	StateMachine = CreateDefaultSubobject<UUStateMachineComponent>(TEXT("StateMachine"));
}

void APaddle::OnBallHit()
{

}

void APaddle::OnMiss()
{
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

	// Start in Idle State
    StateMachine->InitializeState(NewObject<UPaddleStateIdle>(this));
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APaddle::Move(float AxisValue)
{
	// Set Last Input Direction Ball Interaction
	MovementAxisValue = AxisValue;

	UE_LOG(LogTemp, Log, TEXT("Move Axis Value: %.2f!\n"), MovementAxisValue);

	if (FMath::Abs(AxisValue) > 0.1f) // Avoid small floating point movements
    {
		// Change state to Moving
		StateMachine->ChangeState(NewObject<UPaddleStateMoving>(this));

		return;
    }

	StateMachine->ChangeState(NewObject<UPaddleStateIdle>(this));
}

void APaddle::MoveAI(float TargetZ, float DeltaTime)
{
	float Step = MoveSpeed * DeltaTime;
    float NewZ = FMath::FInterpTo(GetActorLocation().Z, TargetZ, DeltaTime, Step);
    
    FVector NewLocation = GetActorLocation();
    NewLocation.Z = NewZ;
    SetActorLocation(NewLocation);
}

EPaddleType APaddle::GetPaddleType() const
{
	return PaddleType;
}

void APaddle::SetPaddleType(EPaddleType InPaddleType)
{
	PaddleType = InPaddleType;
}

FVector APaddle::GetSpawnLocationForPaddleType(EPaddleType InPaddleType)
{
	FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);

	switch (InPaddleType)
	{
	case EPaddleType::PLAYER_1:
		{
			SpawnLocation = FVector{ -300.0f, 0.0f, 50.0f };
		}
		break;

	case EPaddleType::PLAYER_2:
	case EPaddleType::AI:
		{
			SpawnLocation = FVector{ 300.0f, 0.0f, 50.0f };
		}
		break;

	case EPaddleType::NONE:
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to Get Spawn Location! Provide a valid PaddleType!"));
		}
		break;
	}

	return SpawnLocation;
}

void APaddle::OnComponentHitImpl(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("Paddle hit something: %s"), *OtherActor->GetName());
}

void APaddle::PlayBounceSoundAtLocation() const
{
	if (!BounceSound)
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to play Sounds: %s"), *BounceSound->GetName());
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(this, BounceSound, GetActorLocation());
}
