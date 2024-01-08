// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/WaveDataAsset.h"

#if WITH_EDITOR
void UWaveDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
		
	// Make sure the arrays are the same size
	if (Enemies.Num() > WaveTimer.Num())
	{
		// Fills the WaveTimer array until it is the same size as the Enemies array
		for (int i = WaveTimer.Num(); i < Enemies.Num(); i++)
		{
			WaveTimer.Add(10.0f);
		}
	}
	else if (Enemies.Num() < WaveTimer.Num())
	{
		WaveTimer.SetNum(Enemies.Num());
	}

	if (Enemies.Num() > EnemyCount.Num())
	{
		// Fills the EnemyCount array until it is the same size as the Enemies array
		for (int i = EnemyCount.Num(); i < Enemies.Num(); i++)
		{
			EnemyCount.Add(1);
		}
	}
	else if (Enemies.Num() < EnemyCount.Num())
	{
		EnemyCount.SetNum(Enemies.Num());
	}
}
#endif

const TSubclassOf<ABaseUnit> UWaveDataAsset::GetEnemies(const int32 Index) const
{
	if (Enemies.Num() == 0 || Enemies.Num() <= Index)
	{
		return nullptr;
	}

	return Enemies[Index];
}
