// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewCamera.h"

// Engine Includes
#include "Camera/CameraComponent.h"

// Sets default values
AViewCamera::AViewCamera()
	: Camera(nullptr)
{
	// Settings it False to save computation
 	PrimaryActorTick.bCanEverTick = false;

	//-- Creating Camera Component to Visiualize the Game --//
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;
	//--

	// Adding Tag for Faster look-up
	Tags.Add(FName("MainCamera"));
}

void AViewCamera::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(InitialCameraLocation);
}

