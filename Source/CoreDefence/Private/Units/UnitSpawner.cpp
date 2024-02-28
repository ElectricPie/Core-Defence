// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitSpawner.h"

#include "Kismet/GameplayStatics.h"
#include "Units/BaseUnit.h"

// Sets default values
UUnitSpawner::UUnitSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UUnitSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void UUnitSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UUnitSpawner::SpawnUnit(const TSubclassOf<ABaseUnit> UnitToSpawn) const
{
	const AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("%s cannot find owner"), *GetName());
		return;
	}
	if (!UnitToSpawn)
	{
		UE_LOG(LogTemp, Error, TEXT("%s attempted to spawn a null unit"), *GetName());
	}
	if (Waypoints.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("%s attempted to set waypoints on unit with empty array"), *GetName());
		return;
	}

	ABaseUnit* NewEnemy = GetWorld()->SpawnActor<ABaseUnit>(
		UnitToSpawn,
		Owner->GetActorLocation(),
		Owner->GetActorRotation()
	);
	
	NewEnemy->SetWaypoints(Waypoints);
}
