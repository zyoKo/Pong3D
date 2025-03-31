// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"

#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "Paddle.h"
#include "PaddleStateHit.h"
#include "UStateMachineComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABall::ABall()
{
 	PrimaryActorTick.bCanEverTick = false;

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

	//-- Initialize the BoxCollider Component --//
	// Physics Properties Override
	BoxCollider->SetSimulatePhysics(true);
	BoxCollider->SetEnableGravity(false);
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
}

void ABall::ResetBall()
{
	// TODO: Impl Reset Ball after Rounds
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	LaunchVelocity = FindRandomLaunchDirection() * MoveSpeed;

	BoxCollider->SetPhysicsLinearVelocity(LaunchVelocity);
}

FVector ABall::FindRandomLaunchDirection()
{
	float ConeAngleInDegrees = FMath::RandRange(-45.0f, 45.0f);
	FVector launchDirection = FMath::VRandCone(FVector::ForwardVector, ConeAngleInDegrees);
	return launchDirection;
}

void ABall::OnComponentHitImpl(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == this) 
	{
		return;
	}

    // Check if it's a paddle
    if (OtherActor->IsA(APaddle::StaticClass()))
    {
        UE_LOG(LogTemp, Log, TEXT("Ball hit a paddle!"));

		// TODO: Move this logic to APaddle
        // Optional: cast and trigger paddle-specific response
        if (APaddle* Paddle = Cast<APaddle>(OtherActor))
        {
            if (UUStateMachineComponent* SM = Paddle->GetComponentByClass<UUStateMachineComponent>())
            {
				Paddle->PlayBounceSoundAtLocation();
                SM->ChangeState(NewObject<UPaddleStateHit>(Paddle));
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Ball hit something else: %s"), *OtherActor->GetName());
    }
}

void ABall::OnComponentBeginOverlapImpl(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Ball Begin Overlap : %s"), *OtherActor->GetName());
}
