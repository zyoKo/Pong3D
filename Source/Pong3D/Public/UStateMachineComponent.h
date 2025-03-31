// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UStateMachineComponent.generated.h"

class UStateBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PONG3D_API UUStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

    UPROPERTY()
    UStateBase* PreviousState;

    UPROPERTY()
    UStateBase* CurrentState;

public:
    // Default-Constructor
    UUStateMachineComponent();

    UFUNCTION(BlueprintCallable)
    void InitializeState(UStateBase* InitialState);

    UFUNCTION(BlueprintCallable)
    void ChangeState(UStateBase* NewState);

    UFUNCTION(BlueprintCallable)
    UStateBase* GetCurrentState() const;

    UFUNCTION(BlueprintCallable)
    UStateBase* GetPreviousState() const;

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
