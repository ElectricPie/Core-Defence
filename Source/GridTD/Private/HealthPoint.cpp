 // Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPoint.h"

#include "HealthOrb.h"
#include "HealthOrbSocket.h"
#include "HealthOrbContainer.h"
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

	// Create health orbs equal to the MaxOrbs amount and position them around the Orbit centre
	for (uint32 i = 0; i < MaxOrbs; i++)
	{
		FVector& NewOrbPosition = GetPosFromOrbCircle(360 / MaxOrbs * i);
		
		UE_LOG(LogTemp, Warning, TEXT("New Location %s"), *NewOrbPosition.ToString());

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

	TowerPlayerController = Cast<ATowerDefencePlayer>(GetWorld()->GetFirstPlayerController());
	if (!TowerPlayerController) return;
	TowerPlayerController->RegisterPlayerHealth(MaxOrbs);
}

void AHealthPoint::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// Assigns an orb to the actor if it has a Orb socket and there are orbs to give
	UHealthOrbSocket* OrbSocket = OtherActor->FindComponentByClass<UHealthOrbSocket>();
	if (!OrbSocket || HealthOrbs.Num() == 0) return;
	if (OrbSocket->HasOrb()) return;

	const FOrbLocation* OrbLocation = HealthOrbs.Pop();
	UnusedOrbLocations.Add(OrbLocation->OrbPosition);
	
	OrbSocket->AssignHealthOrb(OrbLocation->HealthOrb);
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
		OrbDistanceFromCentre * FMath::Cos(Angle),
		OrbDistanceFromCentre * FMath::Sin(Angle),
		0);
	
	return *Pos;
}

 void AHealthPoint::SetOrbsPosition(AHealthOrb& HealthOrb, const FVector& OrbRelativePos) const
 {
	HealthOrb.AttachToComponent(HealthOrbOrbitCentre, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	UE_LOG(LogTemp, Warning, TEXT("Location %s"), *OrbRelativePos.ToString());
	HealthOrb.SetActorRelativeLocation(OrbRelativePos);
 }

 bool AHealthPoint::AddOrb(FHealthOrbContainer& OrbContainer)
 {
	if (UnusedOrbLocations.Num() == 0) return false;
	
	FVector OrbLocation = UnusedOrbLocations.Pop();
	FOrbLocation(OrbContainer, OrbLocation);
	SetOrbsPosition(OrbContainer.GetHealthOrb(), OrbLocation);
	
	return true;
 }
