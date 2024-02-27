// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitSpawner.generated.h"

class ALevelSettings;
class ABaseUnit;

UCLASS(ClassGroup=(Units), meta=(BlueprintSpawnableComponent))
class COREDEFENCE_API UUnitSpawner : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UUnitSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SpawnUnit(const TSubclassOf<ABaseUnit> UnitToSpawn) const;

private:
	// This will need changing if deciding to use A* later
	UPROPERTY(EditAnywhere, Category = "Pathing", meta = (AllowPrivateAccess=true))
	TArray<AActor*> Waypoints;
};
