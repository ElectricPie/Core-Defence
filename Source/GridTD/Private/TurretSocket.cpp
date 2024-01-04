// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretSocket.h"

#include "TowerDefencePlayer.h"
#include "Turret.h"
#include "DataAssets/TurretDataAsset.h"

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

// TODO: Handle not enough resources on UI by returning false
void ATurretSocket::AddTurret(const UTurretDataAsset* TurretDataAsset, ATowerDefencePlayer* OwningPlayer)
{
	if (TurretInSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("Attempted to assigne turret to occupied turret socket"));
		return;
	}

	if (!OwningPlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("Attempted to assign turret with null player"));
		return;
	}
	
	// TODO: Handle not enough resources on UI
	if (OwningPlayer->GetResources() < TurretDataAsset->GetCost()) { return; }
	
	TurretInSocket = GetWorld()->SpawnActor<ATurret>(
		TurretDataAsset->GetTurretClass(),
		Socket->GetComponentLocation(),
		Socket->GetComponentRotation()
	);
	
	TurretInSocket->AttachToComponent(Socket, FAttachmentTransformRules::KeepWorldTransform);
}

bool ATurretSocket::HasTurret() const
{
	if (TurretInSocket)
	{
		return true;
	}
	
	return false;
}

