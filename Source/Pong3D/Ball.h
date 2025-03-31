// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class PONG3D_API ABall : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "BoxCollider")
	UBoxComponent* BoxCollider;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MoveSpeed = 1000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector LaunchVelocity;
	
public:	
	// Sets default values for this actor's properties
	ABall();

	void ResetBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector FindRandomLaunchDirection();

	UFUNCTION()
	void OnComponentHitImpl(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnComponentBeginOverlapImpl(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
