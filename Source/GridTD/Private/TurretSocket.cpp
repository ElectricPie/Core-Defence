// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretSocket.h"

#include "TowerDefencePlayer.h"
#include "Turret.h"
#include "DataAssets/TurretDataAsset.h"
#include "Enums/ETurretBuildErrors.h"

// Sets default values
ATurretSocket::ATurretSocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = MeshComponent;

	Socket = CreateDefaultSubobject<USceneComponent>(TEXT("Turret Socket"));
	Socket->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATurretSocket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurretSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ETurretBuildErrors ATurretSocket::BuildTurret(const UTurretDataAsset* TurretDataAsset,
                                              ATowerDefencePlayer* OwningPlayer)
{
	if (TurretInSocket) { return SocketOccupied; }
	if (!TurretDataAsset) { return NullDataAsset; }
	if (!OwningPlayer) { return NullPlayerReference; }
	
	if (OwningPlayer->GetResources() < TurretDataAsset->GetCost()) { return NotEnoughResources; }
	
	OwningPlayer->RemoveResources(TurretDataAsset->GetCost());

	// Create the turret in the world
	TurretInSocket = GetWorld()->SpawnActor<ATurret>(
		TurretDataAsset->GetTurretClass(),
		Socket->GetComponentLocation(),
		Socket->GetComponentRotation()
	);
	
	TurretInSocket->AttachToComponent(Socket, FAttachmentTransformRules::KeepWorldTransform);

	return Success;
}

bool ATurretSocket::HasTurret() const
{
	if (TurretInSocket)
	{
		return true;
	}
	
	return false;
}

