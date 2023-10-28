// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "UnitHealth.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

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

	TWeakObjectPtr<UUnitHealth> UnitHealth = OtherActor->FindComponentByClass<UUnitHealth>();
	if (!UnitHealth.IsValid()) return;
	
	EnemiesInRange.AddUnique(UnitHealth);
	
	if (Target.IsValid()) return;
	
	Target = UnitHealth;
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check for other enemies if no current target
	if (!Target.IsValid())
	{
		if (EnemiesInRange.Num() == 0) return;
		const TWeakObjectPtr<UUnitHealth> NewTarget = EnemiesInRange.Pop();

		// Confirm that the enemies hasn't been destroyed before setting it as the target
		if (!NewTarget.IsValid()) return;
		Target = NewTarget;
	}
	
	
	const FVector TargetPos = Target.Get()->GetOwner()->GetActorLocation();
	RotateToPosition(TargetPos);
	Fire(*Target.Get());
}

void ATurret::RotateToPosition(const FVector& Position)
{
	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Position);
	LookAt.Pitch = 0.f;
	UpdateTurretRotation(LookAt.Yaw + RotationOffset - GetActorRotation().Yaw);
	UpdateTurretPitch(LookAt.Pitch + PitchOffset);
}

void ATurret::Fire(UUnitHealth& UnitHealth)
{
	const float GameTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	if (LastFireTime + FireRate > GameTime) return;
	LastFireTime = GameTime;
	UnitHealth.Hit(Damage);
}


