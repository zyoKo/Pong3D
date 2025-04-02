// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UUStateMachineComponent;

enum class EPaddleType : uint8;

/**
 * APaddle represents a controllable Pong paddle in the game.
 * 
 * Responsibilities:
 * - Handles paddle movement input
 * - Manages collisions and bounce behavior
 * - Plays bounce sounds with cooldown
 * - Interfaces with a State Machine to track paddle state (Idle, Moving, Hit)
 */
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
	// State Machine Variable To Add State Machine Component on Build
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UUStateMachineComponent* StateMachine;

public:
	// Sets default values for this pawn's properties
	APaddle();

	/**
     * Returns the last input axis value used to move the paddle.
     * This value is used to influence ball reflection.
     */
	UFUNCTION()
	float GetMovementAxisValue() const;

	/**
     * Gets the configured movement speed of the paddle.
     */
	float GetMoveSpeed() const;

	/**
     * Returns the paddle's collider component (used for collision logic).
     */
	UPrimitiveComponent* GetCollider() const;

	/*
	 * Setting Delegate Binding in PongPlayerController.cpp
	 *
	 * @param AxisValue Between -1 and 1 indicating movement direction.
	 */
	void Move(float AxisValue);

	/**
     * Returns which player this paddle belongs to (Player 1 or Player 2).
     */
	EPaddleType GetPaddleType() const;

	/**
     * Sets the paddle's player type (Player 1 or Player 2).
     * 
     * @param InPaddleType The type to assign.
     */
	void SetPaddleType(EPaddleType InPaddleType);

	/**
     * Handles hit events when this paddle collides with another object.
     * Primarily used for ball-paddle collision response.
     */
	UFUNCTION()
	void OnComponentHitImpl(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/**
     * Plays the bounce sound when the ball collides with the paddle.
     * Uses a cooldown to prevent audio spam during rapid hits.
     */
	void PlayBounceSoundAtLocation() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
