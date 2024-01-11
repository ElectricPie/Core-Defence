// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitSpawner.h"

#include "Kismet/GameplayStatics.h"
#include "Units/BaseUnit.h"

// Sets default values
AUnitSpawner::AUnitSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUnitSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitSpawner::SpawnUnit(const TSubclassOf<ABaseUnit> UnitToSpawn) const
{
	if (!UnitToSpawn)
	{
		UE_LOG(LogTemp, Error, TEXT("%s attempted to spawn a null unit"), *GetName());
	}

	ABaseUnit* NewEnemy = GetWorld()->SpawnActor<ABaseUnit>(
		UnitToSpawn,
		GetActorLocation(),
		GetActorRotation()
	);

	NewEnemy->SetWaypoints(Waypoints);
}
