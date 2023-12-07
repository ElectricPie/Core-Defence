// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenceHudWidget.generated.h"

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
	
	
private:
	void SetUpWidgets() const;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URadialSelectionWidget* TurretSelectionWidget;

	UPROPERTY()
	UPanelSlot* Panel;

	UFUNCTION(BlueprintNativeEvent)
	void SelectTurretSocket(ATurretSocket* TurretSocket);
	
	void CloseTurretSelectionWidget() const;
};
