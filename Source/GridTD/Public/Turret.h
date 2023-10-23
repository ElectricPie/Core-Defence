// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class ABasicEnemy;
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

	void RotateToTarget();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Componets")
	USkeletalMeshComponent* TurretBaseMesh;
	UPROPERTY(VisibleAnywhere, Category="Componets")
	USphereComponent* SphereTriggerArea;
	
	UPROPERTY(VisibleAnywhere, Category="Target")
	ABasicEnemy* Target;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTurretRotation(float Rotation);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTurretPitch(float Pitch);
};
