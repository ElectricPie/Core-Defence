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
	// Consider making this a map instead of an array but there will be a lot more data need for a map to handle
	UPROPERTY(EditAnywhere, Category="Turret Upgrade Path", meta=(AllowPrivateAccess=true))
	TArray<UTurretDataAsset*> TurretUpgradePath;

public:
	UFUNCTION()
	TArray<UTurretDataAsset*> GetUpgradePath() const { return TurretUpgradePath; };
};
