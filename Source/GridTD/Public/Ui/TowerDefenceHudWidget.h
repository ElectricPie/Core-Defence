// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenceHudWidget.generated.h"

class UPlayerResourceWidget;
class ATurretSocket;
class ATurret;
class URadialSelectionWidget;
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
	TSubclassOf<ATurret> GunTurretBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets")
	TSubclassOf<ATurret> CannonTurretBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets")
	TSubclassOf<ATurret> RocketTurretBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets")
	TSubclassOf<ATurret> PiercingTurretBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets")
	TSubclassOf<ATurret> SlowTurretBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turrets")
	TSubclassOf<ATurret> BuffTurretBlueprint;

	UPROPERTY(BlueprintReadOnly)
	ATurretSocket* SelectedTurretSocket;
	
public:
	UPROPERTY()
	UPanelSlot* Panel;

	UFUNCTION()
	void SelectTurretSocket(ATurretSocket* TurretSocket);

	UFUNCTION(BlueprintImplementableEvent)
	void SelectedTurretEvent();
	
	void CloseTurretSelectionWidget() const;

	// Resource widget
	void ClearHealth() const;
	void AddHealth(uint32 HealthOrbCount) const;
};
