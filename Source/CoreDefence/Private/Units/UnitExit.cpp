// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitExit.h"

#include "TowerDefencePlayer.h"
#include "Components/BoxComponent.h"
#include "Health/HealthOrbSocket.h"
#include "Units/BaseUnit.h"

// Sets default values
AUnitExit::AUnitExit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	RootComponent = TriggerVolume;
}

// Called when the game starts or when spawned
void AUnitExit::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ATowerDefencePlayer>(GetWorld()->GetFirstPlayerController());
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("%s cannot find player!"), *GetName());
	}
}

void AUnitExit::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

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

// Called every frame
void AUnitExit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

