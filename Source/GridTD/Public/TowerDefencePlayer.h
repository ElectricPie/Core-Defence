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
	void RegisterPlayerHealth(int32 AdditionalHealth);
};
