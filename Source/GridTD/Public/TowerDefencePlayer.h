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

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	uint32 MaxHealth;
	
	UPROPERTY(VisibleAnywhere)
	uint32 Health;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void GameOver();

public:
	/**
	 * Gives the player the provided amount of health
	 * @param AdditionalHealth The amount of health points to give to the player
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterPlayerHealth(int32 AdditionalHealth);
	
	/**
	 * Reduces the players health by 1
	 */
	UFUNCTION(BlueprintCallable)
	void ReduceHealth();
};
