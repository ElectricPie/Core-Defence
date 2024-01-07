// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TurretUpgradePathDataAsset.generated.h"

class UTurretDataAsset;
/**
 * 
 */
UCLASS()
class GRIDTD_API UTurretUpgradePathDataAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	// TODO: May be worth making this a map with the cost as the other value, things like the tool tip would still be in the data 
	// TODO: this way the can be multiple paths using the same turret but with different costs
	// Consider making this a map instead of an array but there will be a lot more data need for a map to handle
	UPROPERTY(EditAnywhere, Category="Turret Upgrade Path", meta=(AllowPrivateAccess=true))
	TArray<UTurretDataAsset*> TurretUpgradePath;

public:
	UFUNCTION()
	TArray<UTurretDataAsset*> GetUpgradePath() const { return TurretUpgradePath; };
};
