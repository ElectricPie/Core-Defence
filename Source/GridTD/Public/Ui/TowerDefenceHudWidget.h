// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenceHudWidget.generated.h"

class UCanvasPanel;
class UImage;
class URadialSelectionWidget;
class UCanvasPanelSlot;
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
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URadialSelectionWidget* TurretSelectionWidget;

	UPROPERTY()
	UPanelSlot* Panel;

	UFUNCTION(BlueprintNativeEvent)
	void MoveTurretSelectionWidgetToMouse();

	void CloseTurretSelectionWidget() const;
};
