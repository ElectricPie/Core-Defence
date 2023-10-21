// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPoint.h"

#include "DrawDebugHelpers.h"
#include "HealthOrb.h"
#include "TowerDefencePlayer.h"
#include "Components/BoxComponent.h"

// Sets default values
AHealthPoint::AHealthPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetCollisionProfileName(TEXT("IgnoreAll"));

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	TriggerVolume->SetupAttachment(RootComponent);

	HealthOrbOrbitCentre = CreateDefaultSubobject<USceneComponent>(TEXT("Orb Orbit Centre"));
	HealthOrbOrbitCentre->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHealthPoint::BeginPlay()
{
	Super::BeginPlay();
	
	for (uint32 i = 0; i < MaxOrbs; i++)
	{
		AHealthOrb* NewOrb = GetWorld()->SpawnActor<AHealthOrb>(
			HealthOrbBlueprint,
			GetPosFromOrbCircle(360 / MaxOrbs * i),
			GetActorRotation()
		);
		NewOrb->AttachToComponent(HealthOrbOrbitCentre, FAttachmentTransformRules::KeepWorldTransform);
		HealthOrbs.Add(NewOrb);
	}

	TowerPlayerController = Cast<ATowerDefencePlayer>(GetWorld()->GetFirstPlayerController());
	if (!TowerPlayerController) return;
	TowerPlayerController->RegisterPlayerHealth(MaxOrbs);
}

void AHealthPoint::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

// Called every frame
void AHealthPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	HealthOrbOrbitCentre->AddLocalRotation(FRotator(0.f, OrbRotationSpeed, 0.f ), false);
}

FVector& AHealthPoint::GetPosFromOrbCircle(float Angle) const
{
	Angle = 2 * PI * (FMath::Clamp<float>(Angle, 0, 360) / 360);

	FVector* Pos = new FVector(
		HealthOrbOrbitCentre->GetComponentLocation().X,
		HealthOrbOrbitCentre->GetComponentLocation().Y,
		HealthOrbOrbitCentre->GetComponentLocation().Z);
	
	Pos->X += OrbDistanceFromCentre * FMath::Cos(Angle);
	Pos->Y += OrbDistanceFromCentre * FMath::Sin(Angle);
	
	return *Pos;
}

AHealthOrb* AHealthPoint::TakeHealthOrb()
{
	AHealthOrb* HealthOrb = nullptr;
	
	if (HealthOrbs.Num() == 0) return HealthOrb;
	
    HealthOrb = HealthOrbs.Pop();
	return HealthOrb;
}

