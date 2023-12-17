// Fill out your copyright notice in the Description page of Project Settings.


#include "Health/HealthOrbSocket.h"

#include "Health/HealthOrb.h"
#include "Health/HealthOrbContainer.h"
#include "Health/HealthPoint.h"

// Sets default values for this component's properties
UHealthOrbSocket::UHealthOrbSocket()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthOrbSocket::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UHealthOrbSocket::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (!HealthOrb) return;
	delete HealthOrb;
}


// Called every frame
void UHealthOrbSocket::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UHealthOrbSocket::AssignHealthOrb(FHealthOrbContainer& HealthOrbToAssign)
{
	if (HealthOrb) return false;
	
	HealthOrb = &HealthOrbToAssign;
	HealthOrb->GetHealthOrb().AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	return true;
}

bool UHealthOrbSocket::HasOrb() const
{
	if (HealthOrb)
	{
		return true;
	}

	return false;
}

void UHealthOrbSocket::ReturnOrb()
{
	if (!HealthOrb) return;
	HealthOrb->GetOrbOrigin().AddOrb(*HealthOrb);
	HealthOrb = nullptr;
}



