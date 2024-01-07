// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretSocket.h"

#include "TowerDefencePlayer.h"
#include "Turret.h"
#include "DataAssets/TurretDataAsset.h"
#include "Enums/ETurretBuildErrors.h"
#include "TurretSocketRefComponent.h"
#include "Enums/ETurretUpgradeErrors.h"

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

void ATurretSocket::CreateTurret(const TSubclassOf<ATurret> TurretDataAsset)
{
	// Clear the turret in the socket if there is one
	if (TurretInSocket)
	{
		TurretInSocket->Destroy();
	}
	
	// Create the turret in the world
	TurretInSocket = GetWorld()->SpawnActor<ATurret>(
		TurretDataAsset,
		Socket->GetComponentLocation(),
		Socket->GetComponentRotation()
	);
	
	TurretInSocket->AttachToComponent(Socket, FAttachmentTransformRules::KeepWorldTransform);
	
	// Set up a reference to this socket in the turret
	UTurretSocketRefComponent* TurretSocketRef = NewObject<UTurretSocketRefComponent>(TurretInSocket, UTurretSocketRefComponent::StaticClass());
	TurretSocketRef->RegisterComponent();
	TurretSocketRef->SetTurretSocket(this);
}

ETurretBuildErrors ATurretSocket::BuildTurret(const UTurretUpgradePathDataAsset* TurretUpgradeDataAsset, ATowerDefencePlayer* NewOwner)
{
	if (TurretInSocket) { return TurretBuildSocketOccupied; }
	if (!TurretUpgradeDataAsset) { return TurretBuildNullUpgradePath; }
	if (TurretUpgradeDataAsset->GetUpgradePath().Num() == 0) { return TurretBuildEmptyUpgradePath; }
	if (!NewOwner) { return TurretBuildNullPlayerReference; }

	const UTurretDataAsset* TurretDataAsset = TurretUpgradeDataAsset->GetUpgradePath()[0];
	if (!TurretDataAsset) { return TurretBuildNullDataAsset; }
	
	if (NewOwner->GetResources() < TurretDataAsset->GetCost()) { return TurretBuildNotEnoughResources; }
	
	// Keep a reference to the player and remove the cost of the turret
	OwningPlayer = NewOwner;
	OwningPlayer->RemoveResources(TurretDataAsset->GetCost());
	
	// Keep a reference to the turret data asset
	TurretInSocketUpgradeDataAsset = TurretUpgradeDataAsset;
	
	CreateTurret(TurretDataAsset->GetTurretClass());

	// Reset the turret upgrade index to the next upgrade
	TurretUpgradeIndex = 1;
	
	return TurretBuildSuccess;
}

ETurretUpgradeErrors ATurretSocket::UpgradeTurret(ATowerDefencePlayer* UpgradingPlayer)
{
	if (!UpgradingPlayer) { return TurretUpgradeNullPlayerReference; }
	if (!TurretInSocket) { return TurretUpgradeNoTurretInSocket; }
	if (!TurretInSocketUpgradeDataAsset) { return TurretUpgradeNullUpgradePath; }
	if (IsTurretMaxLevel()) { return TurretUpgradeEndOfUpgradePath; }

	// Get the next turret upgrade
	const UTurretDataAsset* TurretUpgradeDataAsset = TurretInSocketUpgradeDataAsset->GetUpgradePath()[TurretUpgradeIndex];
	if (!TurretUpgradeDataAsset) { return TurretUpgradeNullDataAsset; }

	// Check if the upgrading player has enough resources and remove the cost if they do
	if (OwningPlayer->GetResources() < TurretUpgradeDataAsset->GetCost()) { return TurretUpgradeNotEnoughResources; }
	OwningPlayer->RemoveResources(TurretUpgradeDataAsset->GetCost());

	CreateTurret(TurretUpgradeDataAsset->GetTurretClass());
	TurretUpgradeIndex++;

	return TurretUpgradeSuccess;
}

void ATurretSocket::SellTurret(float RefundPercentage)
{
	if (!TurretInSocket) { return; }
	if (!OwningPlayer) { return; }

	RefundPercentage = FMath::Clamp(RefundPercentage, 0.f, 1.f);
	
	// Return the resources to the player
	// TODO: Handle refund including upgrades
	float TotalResources = 0;
	for (int32 i = 0; i < TurretUpgradeIndex; i++)
	{
		TotalResources += TurretInSocketUpgradeDataAsset->GetUpgradePath()[i]->GetCost();
	}

	OwningPlayer->AddResources(TotalResources * RefundPercentage);
	OwningPlayer = nullptr;

	// Destroy the turret
	TurretInSocket->Destroy();
	TurretInSocket = nullptr;
	TurretInSocketUpgradeDataAsset = nullptr;
}

bool ATurretSocket::HasTurret() const
{
	if (TurretInSocket)
	{
		return true;
	}
	
	return false;
}

bool ATurretSocket::IsTurretMaxLevel() const
{
	return TurretUpgradeIndex >= TurretInSocketUpgradeDataAsset->GetUpgradePath().Num();
}

