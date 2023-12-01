// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenceHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class GRIDTD_API UTowerDefenceHudWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	
private:
	void SetUpWidgets() const;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* TurretSelectionWidget;
	
};
