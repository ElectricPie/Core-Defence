// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefencePlayer.h"


void ATowerDefencePlayer::BeginPlay()
{
	Super::BeginPlay();

	GameOver();
}

void ATowerDefencePlayer::GameOver_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Boop"));
}


void ATowerDefencePlayer::RegisterPlayerHealth(int32 AdditionalHealth)
{
	MaxHealth += AdditionalHealth;
	Health += AdditionalHealth;
}

void ATowerDefencePlayer::ReduceHealth()
{
	Health--;

	if (Health > 0) return;
	GameOver();
}
