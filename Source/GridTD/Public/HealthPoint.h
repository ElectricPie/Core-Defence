// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPoint.generated.h"

class FHealthOrbContainer;
class AHealthOrb;
class ATowerDefencePlayer;
class UBoxComponent;

UCLASS()
class GRIDTD_API AHealthPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	struct FOrbLocation
	{
		FOrbLocation(FHealthOrbContainer& Orb, FVector& Position): HealthOrb(Orb), OrbPosition(Position) {}

		FHealthOrbContainer& HealthOrb;
		FVector& OrbPosition;
	};
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* TriggerVolume;
	UPROPERTY(VisibleAnywhere, Category="Components", meta=(ToolTip="The point health orbs will orbit around"))
	USceneComponent* HealthOrbOrbitCentre;

	UPROPERTY(EditAnywhere, Category="Health Orbs", meta=(ClampMin=0.f, UIMin=0.f, AllowPrivateAccess=true))
	float OrbDistanceFromCentre = 100.f;
	UPROPERTY(EditAnywhere, Category="Health Orbs", meta=(AllowPrivateAccess=true))
	uint32 MaxOrbs;
	UPROPERTY(EditAnywhere, Category="Health Orbs", meta=(AllowPrivateAccess=true))
	TSubclassOf<AHealthOrb> HealthOrbBlueprint;
	UPROPERTY(EditAnywhere, Category="Health Orbs", meta=(AllowPrivateAccess=true, ToolTip="How many degrees per second the orbs will rotate"))
	float OrbRotationSpeed = 1.f;

	// TArray<FHealthOrbContainer*> HealthOrbs;
	TArray<FOrbLocation*> HealthOrbs;
	TArray<FVector> UnusedOrbLocations;
	
	UPROPERTY()
	ATowerDefencePlayer* TowerPlayerController;

	FVector& GetPosFromOrbCircle(float Angle) const;

	void SetOrbsPosition(AHealthOrb& HealthOrb, const FVector& OrbRelativePos) const;
	
public:
	/**
	 * Attempts to add the orb to an empty space
	 * @param OrbContainer The orb to be added
	 * @return Returns true if there was space to add the orb
	 */
	bool AddOrb(FHealthOrbContainer& OrbContainer);
};