// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "UnitHealth.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

void ATurret::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UUnitHealth* UnitHealth = OtherActor->FindComponentByClass<UUnitHealth>();
	if (!UnitHealth) return;
	if (Target) return;

	Target = UnitHealth;
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateToTarget();
}

void ATurret::RotateToTarget()
{
	if (!Target) return;

	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetOwner()->GetActorLocation());
	LookAt.Pitch = 0.f;
	UpdateTurretRotation(LookAt.Yaw + RotationOffset - GetActorRotation().Yaw);
	UpdateTurretPitch(LookAt.Pitch + PitchOffset);
}


