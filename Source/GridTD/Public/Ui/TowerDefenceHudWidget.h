// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Health/HealthOrbState.h"
#include "Enums/ETurretType.h"
#include "TowerDefenceHudWidget.generated.h"


class UTurretDataAsset;
class ATowerDefencePlayer;
class UPlayerResourceWidget;
class ATurretSocket;
class ATurret;
class URadialSelectionWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurretButtonClickedSignature, ETurretType, TurretType);

/**
 * 
 */
UCLASS()
class GRIDTD_API UTowerDefenceHudWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	ATowerDefencePlayer* OwningPlayer;
	
	void SetUpWidgets() const;
	
	UFUNCTION()
	void BuildGunTurret();
	UFUNCTION()
	void BuildCannonTurret();
	UFUNCTION()
	void BuildRocketTurret();
	UFUNCTION()
	void BuildPiercingTurret();
	UFUNCTION()
	void BuildSlowTurret();
	UFUNCTION()
	void BuildBuffTurret();


protected:
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	URadialSelectionWidget* TurretSelectionWidget;
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	UPlayerResourceWidget* ResourceWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets")
	UTurretDataAsset* GunTurretBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets")
	UTurretDataAsset* CannonTurretBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets")
	UTurretDataAsset* RocketTurretBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets")
	UTurretDataAsset* PiercingTurretBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets")
	UTurretDataAsset* SlowTurretBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets")
	UTurretDataAsset* BuffTurretBlueprint;

	UPROPERTY(BlueprintReadOnly)
	ATurretSocket* SelectedTurretSocket;
	
public:
	UPROPERTY()
	UPanelSlot* Panel;

	// TODO: Move to private and add function for setting up
	FTurretButtonClickedSignature TurretButtonClickedEvent;

	UFUNCTION()
	void SelectTurretSocket(ATurretSocket* TurretSocket);

	UFUNCTION(BlueprintImplementableEvent)
	void SelectedTurretEvent();
	
	void CloseTurretSelectionWidget() const;

	// Resource widget
	void ClearHealth() const;
	void AddHealth(uint32 HealthOrbCount) const;

	void ChangeOrbState(EHealthOrbState OrbState);

	void UpdateResources(int32 Value) const;
};