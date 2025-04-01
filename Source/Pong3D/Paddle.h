// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UUStateMachineComponent;

enum class EPaddleType : uint8;

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
	EPaddleType PaddleType;

	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	USoundBase* BounceSound;

	// Fixing Sound Spam
	mutable float LastSoundTime = -1.0f;

	// Max delay between playing sounds
	float SoundCooldown = 0.2f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UUStateMachineComponent* StateMachine;

public:
	// Sets default values for this pawn's properties
	APaddle();

	UFUNCTION()
	float GetMovementAxisValue() const;

	float GetMoveSpeed() const;

	UPrimitiveComponent* GetCollider() const;

	/*
	 * Setting Delegate Binding in PongPlayerController.cpp
	 */
	void Move(float AxisValue);

	EPaddleType GetPaddleType() const;

	void SetPaddleType(EPaddleType InPaddleType);

	UFUNCTION()
	void OnComponentHitImpl(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void PlayBounceSoundAtLocation() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
