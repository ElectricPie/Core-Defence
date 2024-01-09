// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class UUnitHealth;
class USphereComponent;

UCLASS()
class COREDEFENCE_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Need to track the current rotation as the animation controls the rotation not the actor
	FRotator CurrentRotation;
	
	float CurrentPitch = 0.f;
	
	float FireCounter = 0.f;
	float LastFireTime = 0.f;


	TArray<TWeakObjectPtr<UUnitHealth>> EnemiesInRange;
	
	void RotateToPosition(const FVector& TargetPosition, const float DeltaTime);
	void Fire(UUnitHealth& Target);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Componets")
	USkeletalMeshComponent* TurretBaseMesh;
	UPROPERTY(VisibleAnywhere, Category="Componets")
	USphereComponent* SphereTriggerArea;
	
	UPROPERTY(EditAnywhere, Category="Animation")
	float RotationOffset = 270.f;
	UPROPERTY(EditAnywhere, Category="Animation", meta=(ClampMin=0.f, UIMin=0.f))
	float RotationSpeedModifier = 120.f;
	UPROPERTY(EditAnywhere, Category="Animation")
	float PitchOffset = 90.f;
	UPROPERTY(EditAnywhere, Category="Animation", meta=(ClampMin=0.f, ClampMax=1.f, UIMin=0.f, UIMax=1.f,
		Tooltip="How closly to facing the target the turrent needs to be before it can fire (1 = Directly facing target, 0 = can fire from 90 degrees from target)"))
	float TurretFiringArch = 0.9f;

	UPROPERTY(EditAnywhere, Category="Fire Power", meta=(ToolTip="The number of seconds between firing", ClampMin=0, UIMin=0))
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere, Category="Fire Power", meta=(ClampMin=0, UIMin=0))
	int32 Damage = 2;

	TWeakObjectPtr<UUnitHealth> Target;
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTurretRotation(float Rotation);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTurretPitch(float Pitch);

	UFUNCTION(BlueprintImplementableEvent)
	void OnFireEvent();
};
