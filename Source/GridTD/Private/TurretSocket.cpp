// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretSocket.h"

#include "Turret.h"

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

void ATurretSocket::AddTurret(TSubclassOf<ATurret> TurretBlueprint)
{
	if (TurretInSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("Attempted to assigne turret to occupied turret socket"));
		return;
	}
	
	if (!TurretBlueprint)
	{
		UE_LOG(LogTemp, Error, TEXT("Attempted to assign turret with null value"));
		return;
	}
	
	TurretInSocket = GetWorld()->SpawnActor<ATurret>(
		TurretBlueprint,
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

