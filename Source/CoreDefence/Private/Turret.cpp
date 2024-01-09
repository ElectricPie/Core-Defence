// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Units/UnitHealth.h"
#include "Components/SphereComponent.h"
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

	// Sets the turret to face forward
	UpdateTurretRotation(CurrentRotation.Yaw + RotationOffset - GetActorRotation().Yaw);
	UpdateTurretPitch(CurrentRotation.Pitch + PitchOffset);
}

void ATurret::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const TWeakObjectPtr<UUnitHealth> UnitHealth = OtherActor->FindComponentByClass<UUnitHealth>();
	if (!UnitHealth.IsValid()) return;

	// Only add the unit if it isn't already in the list
	EnemiesInRange.AddUnique(UnitHealth);
	
	if (Target.IsValid()) return;
	
	Target = UnitHealth;
}

void ATurret::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	const TWeakObjectPtr<UUnitHealth> UnitHealth = OtherActor->FindComponentByClass<UUnitHealth>();
	if (!UnitHealth.IsValid()) return;

	// Remove the unit from possible targets
	EnemiesInRange.Remove(UnitHealth);

	// Remove the target
	if (Target != UnitHealth) return;
	Target.Reset();
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check for other enemies if no current target
	if (!Target.IsValid())
	{
		// Check if there are any enemies in range
		if (EnemiesInRange.Num() == 0) return;

		// TODO: Create a system for differentiating between targets base on how close they are to the end
		// Get the first enemy in range
		const TWeakObjectPtr<UUnitHealth> NewTarget = EnemiesInRange[0];

		// Confirm that the enemies hasn't been destroyed before setting it as the target
		if (!NewTarget.IsValid()) return;
		Target = NewTarget;
	}
	
	const FVector TargetPos = Target.Get()->GetOwner()->GetActorLocation();
	RotateToPosition(TargetPos, DeltaTime);
	
	Fire(*Target.Get());
}

void ATurret::RotateToPosition(const FVector& TargetPosition, const float DeltaTime)
{
	const FRotator TargetRotation = (TargetPosition - GetActorLocation()).Rotation();
	const FRotator DeltaRotation = TargetRotation - CurrentRotation;
	CurrentRotation = FRotator(
		0.f,
		CurrentRotation.Yaw += FMath::Clamp(DeltaRotation.Yaw, -DeltaTime * RotationSpeedModifier, DeltaTime * RotationSpeedModifier),
		CurrentRotation.Roll += FMath::Clamp(DeltaRotation.Roll, -DeltaTime * RotationSpeedModifier, DeltaTime * RotationSpeedModifier)
		);

	UpdateTurretRotation(CurrentRotation.Yaw + RotationOffset - GetActorRotation().Yaw);
	UpdateTurretPitch(CurrentRotation.Pitch + PitchOffset);
}

// Maybe use timer?
void ATurret::Fire(UUnitHealth& TargetHealth)
{
	// Check the turret is facing the target
	FVector TargetRotation = (TargetHealth.GetOwner()->GetActorLocation() - GetActorLocation());
	TargetRotation.Normalize();
	
	FVector CurrentNormalizedRotation = CurrentRotation.Vector();
	CurrentNormalizedRotation.Normalize();
	
	if (FVector::DotProduct(CurrentNormalizedRotation, TargetRotation) < TurretFiringArch) return;
	
	const float GameTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	if (LastFireTime + FireRate > GameTime) return;
	LastFireTime = GameTime;
	OnFireEvent();
	TargetHealth.Hit(Damage);
}


