// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefencePlayer.h"

void ATowerDefencePlayer::RegisterPlayerHealth(int32 AdditionalHealth)
{
	MaxHealth += AdditionalHealth;
	Health += AdditionalHealth;
}
