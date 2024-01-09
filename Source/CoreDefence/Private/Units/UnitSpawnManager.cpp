// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitSpawnManager.h"

#include "DataAssets/WaveDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/LevelSettings.h"
#include "Units/EnemySpawner.h"
#include "Units/BaseUnit.h"


// Sets default values
AUnitSpawnManager::AUnitSpawnManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUnitSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	// Get the wave settings
	ALevelSettings* LevelSettings = Cast<ALevelSettings>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelSettings::StaticClass()));
	if (!LevelSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("%s cannot find LevelSettings actor"), *GetName());
		return;
	}

	WaveDataAsset = LevelSettings->GetWaveDataAsset();
	if (!WaveDataAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("WaveDataAsset is Null"));
	}

	StartNextWave();
}

// Called every frame
void AUnitSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnitSpawnManager::SpawnNextUnit()
{
	// TODO: Switch which spawn point to use
	if (SpawnPoints.Num() == 0) return;
	if (!SpawnPoints[UnitSpawnerIndex]) return;

	// Get the unit to spawn
	const TSubclassOf<ABaseUnit> UnitToSpawn = WaveDataAsset->GetEnemies(CurrentWave);
	if (!UnitToSpawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s attempted to spawn a null unit from %s"), *GetName(), *WaveDataAsset->GetName());
		return;
	}

	SpawnPoints[UnitSpawnerIndex]->SpawnUnit(UnitToSpawn);
	UnitsSpawnedThisWave++;
	
	// Stop spawning units if we have spawned all the units for this wave
	if (UnitsSpawnedThisWave == WaveDataAsset->GetWaveEnemyCount(CurrentWave))
	{
		GetWorld()->GetTimerManager().ClearTimer(CurrentWaveTimerHandle);
	}
}

void AUnitSpawnManager::StartSpawning()
{
	// Reset the spawning counters
	UnitsSpawnedThisWave = 0;
	GetWorld()->GetTimerManager().ClearTimer(CurrentWaveTimerHandle);

	// Setup the timer to spawn the next unit
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &AUnitSpawnManager::SpawnNextUnit);
	GetWorld()->GetTimerManager().SetTimer(CurrentWaveTimerHandle, Delegate, SpawnInterval, true);
}

void AUnitSpawnManager::StartNextWave()
{
	GetWorld()->GetTimerManager().ClearTimer(NextWaveTimerHandle);

	CurrentWave++;

	if (CurrentWave >= WaveDataAsset->GetWaveCount())
	{
		// TODO: Handle end of game
		UE_LOG(LogTemp, Warning, TEXT("No more waves"));
		return;
	}
	
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &AUnitSpawnManager::StartNextWave);
	const float NextWaveTime = WaveDataAsset->GetWaveDelay(CurrentWave);
	GetWorld()->GetTimerManager().SetTimer(NextWaveTimerHandle, Delegate, NextWaveTime, false);

	StartSpawning();
}


