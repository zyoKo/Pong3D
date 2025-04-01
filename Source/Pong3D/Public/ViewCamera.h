// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ViewCamera.generated.h"

class UCameraComponent;

UCLASS()
class PONG3D_API AViewCamera : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector InitialCameraLocation = FVector(0.0f, 1200.0f, 0.0f);

public:	
	// Sets default values for this actor's properties
	AViewCamera();

protected:
	virtual void BeginPlay() override;
};
