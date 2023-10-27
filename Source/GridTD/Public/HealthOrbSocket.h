// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HealthOrbSocket.generated.h"


class FHealthOrbContainer;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRIDTD_API UHealthOrbSocket : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthOrbSocket();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	FHealthOrbContainer* HealthOrb;

public:
	/**
	 * Attempt to assign a HealthOrb to the socket
	 * @param HealthOrbToAssign The HealthOrb to assign to the socket
	 * @return True if the orb was successfully assigned to the socked
	 */
	bool AssignHealthOrb(FHealthOrbContainer& HealthOrbToAssign);

	UFUNCTION(BlueprintCallable)
	bool HasOrb() const;
};
