// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveDataAsset.generated.h"

class ABaseUnit;
/**
 * 
 */
UCLASS()
class GRIDTD_API UWaveDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	UPROPERTY(EditAnywhere, Category = "Wave Data", meta=(ToolTip="The number of enemies in the wave, chaning this will change the size of the WaveTimer and EnemyCount arrays"))
	TArray<TSubclassOf<ABaseUnit>> Enemies;
	UPROPERTY(EditAnywhere, Category = "Wave Data", meta=(ToolTip="The time before the next wave starts, the size of this array can be changed by changing the size of the Enemies array"))
	TArray<float> WaveTimer;
	UPROPERTY(EditAnywhere, Category = "Wave Data", meta=(ToolTip="The number of enemies to spawn for the wave, the size of this array can be changed by changing the size of the Enemies array"))
	TArray<int32> EnemyCount;

	UPROPERTY(EditAnywhere, Category = "Default Values")
	float DefaultWaveTimer = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Default Values")
	int32 DefaultEnemyCount = 1;

public:
	const TSubclassOf<ABaseUnit> GetEnemies(int32 Index) const;
};
