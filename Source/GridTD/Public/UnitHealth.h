// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitHealth.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKilledSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class GRIDTD_API UUnitHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUnitHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere)
	int32 MaxHealth = 10.f;
	UPROPERTY(VisibleAnywhere)
	int32 Health = 0.f;

	UPROPERTY(BlueprintAssignable)
	FOnKilledSignature OnKilledEvent;

public:
	void Hit(int32 Damage);
	
};