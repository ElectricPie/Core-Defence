// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveDataAsset.generated.h"

class ABasicEnemy;
/**
 * 
 */
UCLASS()
class GRIDTD_API UWaveDataAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Wave Data")
	TArray<TSubclassOf<ABasicEnemy>> Enemies;

	UPROPERTY(EditAnywhere, Category = "Wave Data")
	TArray<float> WaveTimer;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};
