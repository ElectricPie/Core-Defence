// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/ETurretBuildErrors.h"
#include "TurretSocket.generated.h"

class ATurret;
class ATowerDefencePlayer;


UCLASS()
class GRIDTD_API ATurretSocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretSocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, Category="Components")
	USceneComponent* Socket;
	UPROPERTY()
	ATurret* TurretInSocket;
	UPROPERTY()
	const UTurretDataAsset* TurretInSocketDataAsset;
	UPROPERTY()
	ATowerDefencePlayer* OwningPlayer;

public:
	UFUNCTION(BlueprintCallable)
	ETurretBuildErrors BuildTurret(const UTurretDataAsset* TurretDataAsset, ATowerDefencePlayer* NewOwner);

	
	/**
	 * @brief Adds resources to the owning player and destroys the turret, the amount of resources added is the turret cost multiplied by the refund percentage
	 * @param RefundPercentage Percentage of the turret cost to refund, values between 0 and 1 (Default: 1)
	 */
	UFUNCTION(BlueprintCallable)
	void SellTurret(float RefundPercentage = 1.f);

	/**
	 * Checks if the socket contains a turret
	 * @return True if the socket has a turret
	 */
	bool HasTurret() const;
};
