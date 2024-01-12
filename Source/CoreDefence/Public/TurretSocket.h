// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/TurretUpgradePathDataAsset.h"
#include "GameFramework/Actor.h"
#include "Enums/ETurretBuildErrors.h"
#include "Enums/ETurretUpgradeErrors.h"
#include "TurretSocket.generated.h"

class ATurret;
class ATowerDefencePlayer;


UCLASS()
class COREDEFENCE_API ATurretSocket : public AActor
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
	// Used to keep track of what upgrade the turret is on
	int32 TurretUpgradeIndex = 0;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, Category="Components")
	USceneComponent* Socket;
	UPROPERTY(EditAnywhere, Category="Turret")
	bool HideOnTurretBuild = false;
	UPROPERTY()
	ATurret* TurretInSocket;
	UPROPERTY()
	const UTurretUpgradePathDataAsset* TurretInSocketUpgradeDataAsset;
	UPROPERTY()
	ATowerDefencePlayer* OwningPlayer;
	
	void CreateTurret(const TSubclassOf<ATurret> TurretDataAsset);

public:
	/**
	 * @brief Attempts to build a turret in the socket taking resources from the owning player if successful
	 * @param TurretUpgradeDataAsset The turret upgrade data asset to build
	 * @param NewOwner The player that will own the turret and pay for it
	 * @return ETurretBuildErrors::TurretBuildSuccess if successful, otherwise the error that occurred
	 */
	UFUNCTION(BlueprintCallable)
	ETurretBuildErrors BuildTurret(const UTurretUpgradePathDataAsset* TurretUpgradeDataAsset, ATowerDefencePlayer* NewOwner);

	/**
	 * @brief Attempts to upgrade the turret based on the TurretUpgradeDataAsset that was used to build the turret and
	 * takes resources from the upgrading player if successful
	 * @param UpgradingPlayer The player that will pay for the upgrade
	 * @return ETurretUpgradeErrors::TurretUpgradeSuccess if successful, otherwise the error that occurred
	 */
	UFUNCTION(BlueprintCallable)
	ETurretUpgradeErrors UpgradeTurret(ATowerDefencePlayer* UpgradingPlayer);
	
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

	bool IsTurretMaxLevel() const;
};
