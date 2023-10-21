// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TowerDefencePlayer.generated.h"

/**
 * 
 */
UCLASS()
class GRIDTD_API ATowerDefencePlayer : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	uint32 MaxHealth;
	
	UPROPERTY(VisibleAnywhere)
	uint32 Health;

public:
	/**
	 * Gives the player the provided amount of health
	 * @param AdditionalHealth The amount of health points to give to the player
	 */
	void RegisterPlayerHealth(int32 AdditionalHealth);
	
	/**
	 * Reduces the players health by 1
	 */
	void ReduceHealth();
};
