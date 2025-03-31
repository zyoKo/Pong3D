// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "PaddleType.h"

#include "Paddle.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UUStateMachineComponent;

UCLASS()
class PONG3D_API APaddle : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 600.0f;

	UPROPERTY()
	float MovementAxisValue = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Paddle")
	EPaddleType PaddleType = EPaddleType::NONE;

	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	USoundBase* BounceSound;

public:
	// Sets default values for this pawn's properties
	APaddle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBallHit();

	UFUNCTION()
	void OnMiss();

	UFUNCTION()
	float GetMovementAxisValue() const;

	float GetMoveSpeed() const;

	UPrimitiveComponent* GetCollider() const;

	void Move(float AxisValue);

	void MoveAI(float TargetZ, float DeltaTime);

	EPaddleType GetPaddleType() const;

	void SetPaddleType(EPaddleType InPaddleType);

	static FVector GetSpawnLocationForPaddleType(EPaddleType InPaddleType);

	UFUNCTION()
	void OnComponentHitImpl(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void PlayBounceSoundAtLocation() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UUStateMachineComponent* StateMachine;

    UPROPERTY(EditAnywhere, Category = "Gameplay")
    int32 Lives = 3;

public:	
	
};
