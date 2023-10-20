// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPoint.generated.h"

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
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerVolume;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	uint32 MaxHealth;

	UPROPERTY(VisibleAnywhere)
	uint32 Health;

	UPROPERTY()
	ATowerDefencePlayer* TowerPlayerController;
};
