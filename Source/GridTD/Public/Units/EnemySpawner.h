// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class ALevelSettings;
class ABaseUnit;

UCLASS()
class GRIDTD_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnUnit();

private:
	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (AllowPrivateAccess))
	TSubclassOf<ABaseUnit> EnemyToSpawn;
	
	// This will need changing if deciding to use A* later
	UPROPERTY(EditAnywhere, Category = "Pathing", meta = (AllowPrivateAccess=true))
	TArray<AActor*> Waypoints;
};
