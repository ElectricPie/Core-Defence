// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemy.h"

#include "HealthOrb.h"
#include "HealthPoint.h"


// Sets default values
ABasicEnemy::ABasicEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	RootComponent = StaticMeshComponent;

	OrbSlot = CreateDefaultSubobject<USceneComponent>(TEXT("Orb Slot"));
	OrbSlot->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasicEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	AHealthPoint* HealthPoint = Cast<AHealthPoint>(OtherActor);
	if (!HealthPoint) return;
	
	// Don't need to pick one up if have one already
	if (HealthOrb) return;
	HealthOrb = HealthPoint->TakeHealthOrb();
	// Stop processing if health point doesn't have a orb
	if (!HealthOrb) return;
		
	HealthOrb->AttachToComponent(OrbSlot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (Waypoints.Num() == 0) return;
	if (!Waypoints[CurrentWaypoint]) return;

	const FVector WaypointPos = Waypoints[CurrentWaypoint]->GetActorLocation();
	MoveToCurrentWaypoint(WaypointPos);
	CheckDistanceToTarget();
}

void ABasicEnemy::MoveToCurrentWaypoint(const FVector& Position)
{
	const FVector Direction = (Position - GetActorLocation()).GetSafeNormal();
	const FVector NewLocation = GetActorLocation() + Direction * MovementSpeed * GetWorld()->GetDeltaSeconds();
	SetActorLocation(NewLocation);
}

void ABasicEnemy::CheckDistanceToTarget()
{
	const float DistanceToWaypoint = FVector::Distance(Waypoints[CurrentWaypoint]->GetActorLocation(), GetActorLocation());
	if (DistanceToWaypoint > WaypointTriggerDistance) return;
	if (CurrentWaypoint + 1 < Waypoints.Num())
	{
		CurrentWaypoint++;
	}
	else
	{
		Destroy();
	}
}

void ABasicEnemy::SetWaypoints(const TArray<AActor*>& NewWaypoints)
{
	CurrentWaypoint = 0;
	Waypoints = NewWaypoints;
}

