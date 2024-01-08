// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/WaveDataAsset.h"

void UWaveDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
		
	// Make sure the arrays are the same size
	if (Enemies.Num() > WaveTimer.Num())
	{
		// Fills the WaveTimer array until it is the same size as the Enemies array
		for (int i = WaveTimer.Num(); i < Enemies.Num(); i++)
		{
			WaveTimer.Add(0.0f);
		}
	}
	else if (Enemies.Num() < WaveTimer.Num())
	{
		// TODO: See if possible to work out which enemy element was removed and remove the corresponding element from the WaveTimer array
		WaveTimer.SetNum(Enemies.Num());
	}
}
