// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Components/SphereComponent.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretBaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Turrent Base Mesh"));
	RootComponent = TurretBaseMesh;

	SphereTriggerArea = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Area"));
	SphereTriggerArea->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

