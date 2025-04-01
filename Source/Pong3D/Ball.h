// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UUStateMachineComponent;
class ATriggerBox;
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

public:
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MoveSpeed = 1000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector LaunchVelocity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Triggers")
    ATriggerBox* LeftPlayerTriggerBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Triggers")
    ATriggerBox* RightPlayerTriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bLaunchBall = false;

protected:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    //UUStateMachineComponent* StateMachine;
	
public:	
	// Sets default values for this actor's properties
	ABall();

	UBoxComponent* GetBoxCollider() const;

	void LaunchBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnComponentHitImpl(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnComponentBeginOverlapImpl(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ResetBall();

	void LaunchInRandomDirection();
};
