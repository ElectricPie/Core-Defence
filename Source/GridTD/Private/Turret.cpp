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

	// Sets the turret to face forward
	UpdateTurretRotation(CurrentRotation.Yaw + RotationOffset - GetActorRotation().Yaw);
	UpdateTurretPitch(CurrentRotation.Pitch + PitchOffset);
}

void ATurret::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const TWeakObjectPtr<UUnitHealth> UnitHealth = OtherActor->FindComponentByClass<UUnitHealth>();
	if (!UnitHealth.IsValid()) return;
	
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
		if (EnemiesInRange.Num() == 0) return;
		const TWeakObjectPtr<UUnitHealth> NewTarget = EnemiesInRange.Pop();

		// Confirm that the enemies hasn't been destroyed before setting it as the target
		if (!NewTarget.IsValid()) return;
		Target = NewTarget;
	}
	
	const FVector TargetPos = Target.Get()->GetOwner()->GetActorLocation();
	RotateToPosition(TargetPos, DeltaTime);
	
	// TODO: Only fire when facing enemy
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

void ATurret::Fire(UUnitHealth& UnitHealth)
{
	const float GameTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	if (LastFireTime + FireRate > GameTime) return;
	LastFireTime = GameTime;
	OnFireEvent();
	UnitHealth.Hit(Damage);
}


