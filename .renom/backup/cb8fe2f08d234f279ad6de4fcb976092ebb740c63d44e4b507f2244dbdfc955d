// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitExit.generated.h"

class UBoxComponent;
class ATowerDefencePlayer;

UCLASS()
class GRIDTD_API AUnitExit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitExit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* TriggerVolume;
	
	UPROPERTY()
	ATowerDefencePlayer* Player;
};
