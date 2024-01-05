// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Health/HealthOrbState.h"
#include "Enums/ETurretType.h"
#include "Enums/ETurretSelectionOption.h"
#include "TowerDefenceHudWidget.generated.h"


class UErrorDisplayWidget;
class UPlayerResourceWidget;
class ATurretSocket;
class URadialSelectionWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurretButtonClickedSignature, ETurretType, TurretType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurretSeltionButtonClickedSignature, ETurretSelectionOption, TurretSelectionOption);

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
	UPROPERTY(EditAnywhere, Category="Error Message")
	float ErrorMessageDisplayTime = 3.f;
	
	FTurretButtonClickedSignature TurretButtonClickedEvent;
	FTurretSeltionButtonClickedSignature TurretSelectionButtonClickedEvent;

	FTimerHandle ErrorDisplayTimerHandle;
	
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

	UFUNCTION()
	void SellTurret();


protected:
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	URadialSelectionWidget* TurretBuildWidget;
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	URadialSelectionWidget* TurretSelectedWidget;
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	UPlayerResourceWidget* ResourceWidget;
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	UErrorDisplayWidget* ErrorDisplayWidget;
	
public:
	UPROPERTY()
	UPanelSlot* Panel;

	void AddTurretButtonClickedEvent(const FScriptDelegate& Delegate);
	void AddTurretSelectionButtonClickedEvent(const FScriptDelegate& Delegate);
	
	UFUNCTION()
	void SelectTurretSocket(const ATurretSocket* TurretSocket);

	UFUNCTION(BlueprintImplementableEvent)
	void OpenTurretBuildMenuEvent();
	UFUNCTION(BlueprintImplementableEvent)
	void OpenTurretSelectionMenuEvent();
	
	void CloseTurretBuildWidget() const;
	void CloseTurretSelectionWidget() const;

	// Resource widget
	void ClearHealth() const;
	void AddHealth(uint32 HealthOrbCount) const;

	void ChangeOrbState(EHealthOrbState OrbState);

	void UpdateResources(int32 Value) const;

	void DisplayError(const FText& ErrorMessage);
	void HideErrorMessage() const;
};