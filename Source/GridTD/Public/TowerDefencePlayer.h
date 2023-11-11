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

	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category="Health")
	uint32 MaxHealth;
	UPROPERTY(VisibleAnywhere, Category="Health")
	uint32 Health;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float SelectionRaycastDistance = 2000.f;

	UFUNCTION()
	void Select();

protected:
	UFUNCTION(BlueprintNativeEvent)
	void GameOver();

	/**
	 * Raycast from the screens mouse position to the world
	 * @param HitLocation The location of the raycast hit
	 * @param HitActor The Actor hit by the raycast if it Hits
	 * @return True if the raycast hit an actor
	 */
	UFUNCTION(BlueprintCallable)
	bool RaycastToMouse(FVector& HitLocation, AActor*& HitActor);

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
