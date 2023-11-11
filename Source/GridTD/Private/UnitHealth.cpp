// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitHealth.h"

// Sets default values for this component's properties
UUnitHealth::UUnitHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUnitHealth::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Health = MaxHealth;
}


// Called every frame
void UUnitHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUnitHealth::Hit(const int32 Damage)
{
	Health -= Damage;
	if (Health > 0) return;

	OnKilledEvent.Broadcast();
	GetOwner()->Destroy();
}

