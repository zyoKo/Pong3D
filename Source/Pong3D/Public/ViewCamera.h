// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ViewCamera.generated.h"

class UCameraComponent;

/**
 * AViewCamera is a simple camera actor used to provide a fixed view of the
 * Pong3D playfield. It can be placed in the level or spawned at runtime.
 * 
 * Responsibilities:
 *  - Holds a UCameraComponent as the active view
 *  - Sets its initial position from a configurable vector
 *  - Can be used as a view target from GameMode or PlayerController
 */
UCLASS()
class PONG3D_API AViewCamera : public AActor
{
	GENERATED_BODY()

protected:
	// The camera component providing the actual view for this actor
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

public:
	// Initial location to place the camera when the game starts
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector InitialCameraLocation = FVector(0.0f, 1500.0f, 0.0f);

public:	
	// Constructor that sets default values for this actor
	AViewCamera();

protected:
	/**
	 * Called when the game starts or when the actor is spawned.
	 * Sets the camera to the initial specified location.
	 */
	virtual void BeginPlay() override;
};
