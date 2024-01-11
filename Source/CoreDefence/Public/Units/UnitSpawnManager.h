// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitSpawnManager.generated.h"

class AUnitSpawner;
class UWaveDataAsset;
UCLASS()
class COREDEFENCE_API AUnitSpawnManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUnitSpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category="Spawning")
	TArray<AUnitSpawner*> SpawnPoints;
	UPROPERTY(EditAnywhere, Category= "Spawning")
	float SpawnInterval = 2.f;
	
	UPROPERTY()
	UWaveDataAsset* WaveDataAsset;
	
	int32 UnitSpawnerIndex = 0;

	int32 CurrentWave = -1;
	int32 UnitsSpawnedThisWave = 0;
	
	FTimerHandle NextWaveTimerHandle;
	FTimerHandle CurrentWaveTimerHandle;

	void SpawnNextUnit();
	void StartSpawning();
	void StartNextWave();
};
