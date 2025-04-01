// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewCamera.h"

#include "Camera/CameraComponent.h"

// Sets default values
AViewCamera::AViewCamera()
	: Camera(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;

	Tags.Add(FName("MainCamera"));
}

void AViewCamera::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(InitialCameraLocation);
}

