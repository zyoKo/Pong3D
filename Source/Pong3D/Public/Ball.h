// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UUStateMachineComponent;
class ATriggerBox;
class UBoxComponent;
class UStaticMeshComponent;

/**
 * @class ABall
 * @brief Represents the game ball in Pong3D.
 * 
 * The ABall class handles physics-based movement, collision detection,
 * scoring detection via trigger boxes, and interactions with paddles.
 * It launches with a configurable speed and bounces using physics or scripted logic.
 * 
 * Responsibilities:
 * - Handles movement using velocity or physics forces.
 * - Detects scoring using trigger volumes placed behind each player paddle.
 * - Communicates with the GameMode when a score occurs.
 * - Responds to paddle collisions and adjusts trajectory accordingly.
 * 
 * Exposed to the editor for easy level design and tuning.
 * Can be referenced by PlayerControllers or GameMode for resets and launching.
 * 
 * @see APaddle, APongGameMode, ATriggerBox
 */
UCLASS()
class PONG3D_API ABall : public AActor
{
	GENERATED_BODY()

	// The static mesh that visually represents the ball in the scene
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;
	
	// The box collider used for physics interactions and collision detection
	UPROPERTY(VisibleAnywhere, Category = "BoxCollider")
	UBoxComponent* BoxCollider;

public:
	// The speed at which the ball launches when movement is initiated
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MoveSpeed = 1000.0f;
	
	// The current velocity of the ball, used to drive movement or physics
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector LaunchVelocity;
	
	// The trigger box used to detect when the ball enters the left player's scoring area
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Triggers")
	ATriggerBox* LeftPlayerTriggerBox;
	
	// The trigger box used to detect when the ball enters the right player's scoring area
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Triggers")
	ATriggerBox* RightPlayerTriggerBox;

protected:
	/**
	 * Currently didn't find a need to Add States to Ball due to the scope of the project.
	 *
	 * Even tho can be used to implement other logic later like Material Changes on Events, etc.!?
	 */ 
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    //UUStateMachineComponent* StateMachine;
	
public:	
	// Sets default values for this actor's properties
	ABall();

	/**
	 * Returns the Box Collider to do Physics Related Computation (if and where needed).
	 */
	UBoxComponent* GetBoxCollider() const;

	/*
	 * Press 'Space Bar' to Launch the Ball.
	 */
	void LaunchBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/**
	 * Called when this component hits (collides with) another actor or component.
	 * Used to handle physical collision events such as bouncing the ball off paddles or walls.
	 *
	 * @param HitComponent      The component that registered the hit.
	 * @param OtherActor        The other actor involved in the collision.
	 * @param OtherComp         The component on the other actor that was hit.
	 * @param NormalImpulse     The impulse applied to stop the movement due to the hit.
	 * @param Hit               Detailed hit result including impact point and normal.
	 */
	UFUNCTION()
	void OnComponentHitImpl(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/**
     * Called when this component begins to overlap with another component.
     * Typically used to trigger events like scoring, zone entry, or soft collisions.
     *
     * @param OverlappedComponent   This component that started overlapping.
     * @param OtherActor            The actor that this component overlapped with.
     * @param OtherComp             The specific component that was overlapped.
     * @param OtherBodyIndex        Index of the other body (if multiple).
     * @param bFromSweep            True if the overlap was caused by a sweep movement.
     * @param SweepResult           Detailed result of the sweep (if applicable).
     */
	UFUNCTION()
	void OnComponentBeginOverlapImpl(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/*
	 * Resets the Ball to it's Original/Starting Location and Velocity.
	 */
	void ResetBall();

	/**
	 * Helper function, Launches the Ball in Random Direction in the beginning of the game.
	 */
	void LaunchInRandomDirection();
};
