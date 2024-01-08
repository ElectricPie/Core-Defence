﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitSpawnManager.h"

#include "DataAssets/WaveDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/LevelSettings.h"
#include "Units/EnemySpawner.h"


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

	StartSpawning();
}

// Called every frame
void AUnitSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnitSpawnManager::SpawnNextUnit()
{
	// Switch which spawn point to use

	// Temporally use the first spawn point
	if (SpawnPoints.Num() == 0) return;
	if (!SpawnPoints[0]) return;

	const TSubclassOf<ABaseUnit> UnitToSpawn = WaveDataAsset->GetEnemies(0);

	SpawnPoints[0]->SpawnUnit(UnitToSpawn);
}

void AUnitSpawnManager::StartSpawning()
{
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &AUnitSpawnManager::SpawnNextUnit);
	GetWorld()->GetTimerManager().SetTimer(CurrentWaveTimerHandle, Delegate, SpawnInterval, true);
}


