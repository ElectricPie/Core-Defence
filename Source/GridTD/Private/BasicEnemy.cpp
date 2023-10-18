// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemy.h"

#include "Components/CapsuleComponent.h"

// Sets default values
ABasicEnemy::ABasicEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsual Component"));
	RootComponent = CapsuleComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToCurrentWaypoint();
}

void ABasicEnemy::MoveToCurrentWaypoint()
{
	if (!CurrentTarget) return;

	const FVector Direction = (CurrentTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	const FVector NewLocation = GetActorLocation() + Direction * MovementSpeed * GetWorld()->GetDeltaSeconds();
	SetActorLocation(NewLocation);
}

void ABasicEnemy::SetWaypoints(TArray<AActor*> NewWaypoints)
{
	Waypoints = NewWaypoints;
	
	if (Waypoints.Num() == 0) return;
	if (!Waypoints[0]) return;
	CurrentTarget = Waypoints[0];
}

