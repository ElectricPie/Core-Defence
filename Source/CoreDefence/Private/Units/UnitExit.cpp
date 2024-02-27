// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitExit.h"

#include "Player/TowerDefencePlayer.h"
#include "Components/BoxComponent.h"
#include "Health/HealthOrbSocket.h"
#include "Units/BaseUnit.h"

// Sets default values
UUnitExit::UUnitExit()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UUnitExit::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner())
	{
		UE_LOG(LogTemp, Error, TEXT("%s cannot find owner!"), *GetName());
		return;
	}
	
	Player = Cast<ATowerDefencePlayer>(GetWorld()->GetFirstPlayerController());
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("%s cannot find player!"), *GetName());
	}
	
	if (UShapeComponent* TriggerVolume = Cast<UShapeComponent>(GetOwner()->GetComponentByClass(UBoxComponent::StaticClass())))
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &UUnitExit::OnOverlapBegin);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s cannot find shape component!"), *GetName());
	}
}

// Called every frame
void UUnitExit::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UUnitExit::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Player) return;

	ABaseUnit* Unit = Cast<ABaseUnit>(OtherActor);
	if (!Unit) return;

	// Check if the unit has a health orb
	if (const UHealthOrbSocket* HealthOrbSocket = Cast<UHealthOrbSocket>(Unit->GetComponentByClass(UHealthOrbSocket::StaticClass())))
	{
		// Take health if the unit has an orb
		if (HealthOrbSocket->HasOrb())
		{
			Player->ReduceHealth();
		}
	}

	// Destroy the unit
	Unit->ReachedExit();
}
