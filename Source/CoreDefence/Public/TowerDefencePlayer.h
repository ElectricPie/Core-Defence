// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Health/HealthOrbState.h"
#include "Enums/ETurretType.h"
#include "Enums/ETurretSelectionOption.h"
#include "Enums/ETurretUpgradeErrors.h"
#include "TowerDefencePlayer.generated.h"

class UTurretUpgradePathDataAsset;
class ALevelSettings;
class UTowerDefenceHudWidget;
class UPlayerResourceWidget;
class ATurretSocket;
class UTurretDataAsset;
/**
 * 
 */
UCLASS()
class COREDEFENCE_API ATowerDefencePlayer : public APlayerController
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UTowerDefenceHudWidget> HudWidgetBlueprint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	FText InsufficientResourcesText;
	UPROPERTY(BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	UTowerDefenceHudWidget* HudWidget;
	UPROPERTY(BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	UPlayerResourceWidget* ResourceWidget;
	
	UPROPERTY(VisibleAnywhere, Category="Resources")
	int32 Resources = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets", meta=(AllowPrivateAccess="true"))
	UTurretUpgradePathDataAsset* GunTurretUpgradeDataAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets", meta=(AllowPrivateAccess="true"))
	UTurretUpgradePathDataAsset* CannonTurretUpgradeDataAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets", meta=(AllowPrivateAccess="true"))
	UTurretUpgradePathDataAsset* RocketTurretUpgradeDataAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets", meta=(AllowPrivateAccess="true"))
	UTurretUpgradePathDataAsset* PiercingTurretUpgradeDataAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets", meta=(AllowPrivateAccess="true"))
	UTurretUpgradePathDataAsset* SlowTurretUpgradeDataAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets", meta=(AllowPrivateAccess="true"))
	UTurretUpgradePathDataAsset* BuffTurretUpgradeDataAsset;
	
	UPROPERTY()
	ATurretSocket* SelectedTurretSocket;

	UPROPERTY()
	const ALevelSettings* LevelSettings;
	
	UFUNCTION()
	void Select();

	void SetupUi();

	UFUNCTION()
	void OnOrbStateChanged(EHealthOrbState OrbState);

	UFUNCTION()
	void OnTurretToBuildSelected(ETurretType TurretType);
	void HandleUpgradeError(ETurretUpgradeErrors UpgradeError);

	UFUNCTION()
	void OnTurretSelectionOptionSelected(ETurretSelectionOption TurretSelectionOption);

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

	/**
	 * @brief Attempts to remove the given amount of resources from the player
	 * @param Amount The amount of resources to remove
	 * @return True if the player has enough resources to remove
	 */
	bool RemoveResources(const int32 Amount);

	/**
	 * @brief Adds the given amount of resources to the player
	 * @param Amount The amount of resources to add
	 */
	void AddResources(const int32 Amount);
};