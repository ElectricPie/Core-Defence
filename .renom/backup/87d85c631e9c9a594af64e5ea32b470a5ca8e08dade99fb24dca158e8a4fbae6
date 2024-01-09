// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TurretDataAsset.generated.h"

class ATurret;

/**
 * 
 */
UCLASS()
class GRIDTD_API UTurretDataAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ATurret> TurretClass;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 Cost;

public:
	UFUNCTION()
	TSubclassOf<ATurret> GetTurretClass() const { return TurretClass; }
	UFUNCTION()
	int32 GetCost() const { return Cost; }
};
