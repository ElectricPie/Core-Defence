// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class UUnitHealth;
class USphereComponent;

UCLASS()
class GRIDTD_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float CurrentRotation = 0.f;
	float CurrentPitch = 0.f;
	
	float FireCounter = 0.f;
	float LastFireTime = 0.f;
	
	void RotateToTarget();
	void FireAtTarget();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Componets")
	USkeletalMeshComponent* TurretBaseMesh;
	UPROPERTY(VisibleAnywhere, Category="Componets")
	USphereComponent* SphereTriggerArea;
	
	UPROPERTY(VisibleAnywhere, Category="Target")
	UUnitHealth* Target;
	
	UPROPERTY(EditAnywhere, Category="Animation")
	float RotationOffset = 270.f;
	UPROPERTY(EditAnywhere, Category="Animation")
	float PitchOffset = 90.f;

	UPROPERTY(EditAnywhere, Category="Fire Power", meta=(ToolTip="The number of seconds between firing", ClampMin=0, UIMin=0))
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere, Category="Fire Power", meta=(ClampMin=0, UIMin=0))
	int32 Damage = 2;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTurretRotation(float Rotation);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTurretPitch(float Pitch);
};
