 // Fill out your copyright notice in the Description page of Project Settings.


#include "Health/HealthPoint.h"

#include "Health/HealthOrb.h"
#include "Health/HealthOrbSocket.h"
#include "Health/HealthOrbContainer.h"
#include "Components/BoxComponent.h"

// Sets default values
AHealthPoint::AHealthPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));
	RootComponent = RootSceneComponent;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionProfileName(TEXT("IgnoreAll"));

	HealthOrbOrbitCentre = CreateDefaultSubobject<USceneComponent>(TEXT("Orb Orbit Centre"));
	HealthOrbOrbitCentre->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHealthPoint::BeginPlay()
{
	Super::BeginPlay();

	// Create health orbs equal to the MaxOrbs amount and position them around the Orbit centre
	for (uint32 i = 0; i < MaxOrbs; i++)
	{
		FVector& NewOrbPosition = GetPosFromOrbCircle(360 / MaxOrbs * i);
		
		// Attach the orbs to the orbit then set the location as GetPosFromOrbCircle gives relative pos
		AHealthOrb* NewOrb = GetWorld()->SpawnActor<AHealthOrb>(
			HealthOrbBlueprint,
			HealthOrbOrbitCentre->GetComponentLocation(),
			GetActorRotation()
		);
		NewOrb->AttachToComponent(HealthOrbOrbitCentre, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		NewOrb->SetActorRelativeLocation(NewOrbPosition);

		// Add the orb and its location
		FHealthOrbContainer* NewContainer = new FHealthOrbContainer(*NewOrb, *this);
		FOrbLocation* OrbLocation = new FOrbLocation(*NewContainer, NewOrbPosition);
		HealthOrbs.Add(OrbLocation);
	}
}

void AHealthPoint::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// Assigns an orb to the actor if it has a Orb socket and there are orbs to give
	UHealthOrbSocket* OrbSocket = OtherActor->FindComponentByClass<UHealthOrbSocket>();
	if (!OrbSocket || HealthOrbs.Num() == 0) return;
	if (OrbSocket->HasOrb()) return;

	// Keep track of where the empty space
	const FOrbLocation* OrbLocation = HealthOrbs.Pop();
	UnusedOrbLocations.Add(OrbLocation->OrbPosition);
	
	OrbSocket->AssignHealthOrb(OrbLocation->HealthOrb);
	
	OrbStateChangedEvent.Broadcast(Taken);
}

// Called every frame
void AHealthPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: This isn't accommodating for DeltaTime so rotates much slower at lower FPS
	HealthOrbOrbitCentre->AddLocalRotation(FRotator(0.f, OrbRotationSpeed, 0.f ), false);
}

FVector& AHealthPoint::GetPosFromOrbCircle(float Angle) const
{
	Angle = 2 * PI * (FMath::Clamp<float>(Angle, 0, 360) / 360);

	FVector* Pos = new FVector(
		OrbDistanceFromCentre * FMath::Cos(Angle),
		OrbDistanceFromCentre * FMath::Sin(Angle),
		0);
	
	return *Pos;
}

 void AHealthPoint::SetOrbsPosition(AHealthOrb& HealthOrb, const FVector& OrbRelativePos) const
 {
	HealthOrb.AttachToComponent(HealthOrbOrbitCentre, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	HealthOrb.SetActorRelativeLocation(OrbRelativePos);
 }

 bool AHealthPoint::AddOrb(FHealthOrbContainer& OrbContainer)
 {
	if (UnusedOrbLocations.Num() == 0) return false;

	// Set the orb in a free position
	FVector OrbLocation = UnusedOrbLocations.Pop();
	FOrbLocation* NewOrbLocation = new FOrbLocation(OrbContainer, OrbLocation);
	SetOrbsPosition(OrbContainer.GetHealthOrb(), OrbLocation);
	HealthOrbs.Add(NewOrbLocation);
	
	OrbStateChangedEvent.Broadcast(Stored);
	
	return true;
 }

 uint32 AHealthPoint::GetOrbCount() const
 {
	return HealthOrbs.Num();
 }

 TArray<TWeakPtr<const FHealthOrbContainer>> AHealthPoint::GetHealthOrbs() const
 {
	TArray<TWeakPtr<const FHealthOrbContainer>> Orbs;
	for (const FOrbLocation* Orb : HealthOrbs)
	{
		Orbs.Add(MakeShared<FHealthOrbContainer>(Orb->HealthOrb));
	}

	return Orbs;
 }
