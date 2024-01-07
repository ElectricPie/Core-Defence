// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretSocket.h"

#include "TowerDefencePlayer.h"
#include "Turret.h"
#include "DataAssets/TurretDataAsset.h"
#include "Enums/ETurretBuildErrors.h"
#include "TurretSocketRefComponent.h"

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

ETurretBuildErrors ATurretSocket::BuildTurret(const UTurretUpgradePathDataAsset* TurretUpgradeDataAsset, ATowerDefencePlayer* NewOwner)
{
	if (TurretInSocket) { return SocketOccupied; }
	if (!TurretUpgradeDataAsset) { return NullUpgradePath; }
	if (TurretUpgradeDataAsset->GetUpgradePath().Num() == 0) { return EmptyUpgradePath; }
	if (!NewOwner) { return NullPlayerReference; }

	const UTurretDataAsset* TurretDataAsset = TurretUpgradeDataAsset->GetUpgradePath()[0];
	if (!TurretDataAsset) { return NullDataAsset; }
	
	if (NewOwner->GetResources() < TurretDataAsset->GetCost()) { return NotEnoughResources; }
	
	// Keep a reference to the player and remove the cost of the turret
	OwningPlayer = NewOwner;
	OwningPlayer->RemoveResources(TurretDataAsset->GetCost());
	
	// Keep a reference to the turret data asset
	TurretInSocketUpgradeDataAsset = TurretUpgradeDataAsset;
	
	// Create the turret in the world
	TurretInSocket = GetWorld()->SpawnActor<ATurret>(
		TurretDataAsset->GetTurretClass(),
		Socket->GetComponentLocation(),
		Socket->GetComponentRotation()
	);
	
	TurretInSocket->AttachToComponent(Socket, FAttachmentTransformRules::KeepWorldTransform);
	
	// Set up a reference to this socket in the turret
	UTurretSocketRefComponent* TurretSocketRef = NewObject<UTurretSocketRefComponent>(TurretInSocket, UTurretSocketRefComponent::StaticClass());
	TurretSocketRef->RegisterComponent();
	TurretSocketRef->SetTurretSocket(this);
	
	return Success;
}

void ATurretSocket::SellTurret(float RefundPercentage)
{
	if (!TurretInSocket) { return; }
	if (!OwningPlayer) { return; }

	RefundPercentage = FMath::Clamp(RefundPercentage, 0.f, 1.f);
	
	// Return the resources to the player
	// TODO: Handle refund including upgrades
	// OwningPlayer->AddResources(TurretInSocketDataAsset->GetCost() * RefundPercentage);
	OwningPlayer = nullptr;

	// Destroy the turret
	TurretInSocket->Destroy();
	TurretInSocket = nullptr;
}

bool ATurretSocket::HasTurret() const
{
	if (TurretInSocket)
	{
		return true;
	}
	
	return false;
}

