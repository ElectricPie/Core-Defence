// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/BaseUnit.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABaseUnit::ABaseUnit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));
	RootComponent = RootSceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Waypoints.Num() == 0) return;
	if (!Waypoints[CurrentWaypoint]) return;

	const FVector WaypointPos = Waypoints[CurrentWaypoint]->GetActorLocation();
	MoveToCurrentWaypoint(WaypointPos);
	CheckDistanceToTarget();
}

void ABaseUnit::MoveToCurrentWaypoint(const FVector& Position)
{
	// Move towards the position
	const FVector Direction = (Position - GetActorLocation()).GetSafeNormal();
	const FVector NewLocation = GetActorLocation() + Direction * MovementSpeed * GetWorld()->GetDeltaSeconds();
	SetActorLocation(NewLocation);

	// Rotate the static mesh to face the direction of movement
	const FVector ForwardVector = GetActorForwardVector();
	const FVector NewForwardVector = FMath::VInterpTo(ForwardVector, Direction, GetWorld()->GetDeltaSeconds(), RotationSpeed);
	SetActorRotation(NewForwardVector.Rotation());
}

void ABaseUnit::CheckDistanceToTarget()
{
	const float DistanceToWaypoint = FVector::Distance(Waypoints[CurrentWaypoint]->GetActorLocation(),
	                                                   GetActorLocation());
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

void ABaseUnit::SetWaypoints(const TArray<AActor*>& NewWaypoints)
{
	CurrentWaypoint = 0;
	Waypoints = NewWaypoints;
}

void ABaseUnit::ReachedExit()
{
	OnExit.Broadcast();
	Destroy();
}
