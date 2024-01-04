// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Health/HealthOrbState.h"
#include "Enums/ETurretType.h"
#include "TowerDefencePlayer.generated.h"

class UTowerDefenceHudWidget;
class ATurretSocket;
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
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	float SelectionRaycastDistance = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UTowerDefenceHudWidget> HudWidgetBlueprint;
	UPROPERTY()
	UTowerDefenceHudWidget* HudWidget;
	
	UPROPERTY(VisibleAnywhere, Category="Resources")
	int32 Resources = 100;

	UPROPERTY()
	ATurretSocket* SelectedTurretSocket;
	
	UFUNCTION()
	void Select();

	void SetupUi();

	UFUNCTION()
	void OnOrbStateChanged(EHealthOrbState OrbState);

	UFUNCTION()
	void OnTurretToBuildSelected(ETurretType TurretType);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void GameOver();

	/**
	 * Gets the position of the mouse on the screen
	 * @param MouseScreenPos A FVector to store the mouses position
	 * @return False if no mouse device is detected
	 */
	UFUNCTION()
	bool GetMouseScreenPos(FVector2D& MouseScreenPos) const;
	
	/**
	 * Raycast from the screens mouse position to the world
	 * @param MouseScreenPos The location of the mouse on the screen
	 * @param HitLocation The location of the raycast hit
	 * @param HitActor The Actor hit by the raycast if it Hits
	 * @return True if the raycast hit an actor
	 */
	UFUNCTION(BlueprintCallable)
	bool RaycastToMouse(const FVector2D& MouseScreenPos, FVector& HitLocation, AActor*& HitActor) const;

public:
	/**
	 * Reduces the players health by 1
	 */
	UFUNCTION(BlueprintCallable, Category="Resources")
	void ReduceHealth();

	UFUNCTION(BlueprintPure, Category="Resources")
	int32 GetResources() const { return Resources; }
};
