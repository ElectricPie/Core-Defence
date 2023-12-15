// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/TowerDefenceHudWidget.h"

#include "Components/Image.h"
#include "Ui/PlayerResourceWidget.h"
#include "Ui/RadialSelectionWidget.h"



void UTowerDefenceHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetUpWidgets();
}

void UTowerDefenceHudWidget::SetUpWidgets() const
{
	if (TurretSelectionWidget)
	{
		TurretSelectionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UTowerDefenceHudWidget::SelectTurretSocket_Implementation(ATurretSocket* TurretSocket)
{
}

void UTowerDefenceHudWidget::CloseTurretSelectionWidget() const
{
	if (!TurretSelectionWidget) return;
	TurretSelectionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UTowerDefenceHudWidget::ClearHealth() const
{
	if (ResourceWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("TowerDefenceHud is missing referance to ResourceWidget"));
		return;
	}

	ResourceWidget->ClearOrbWidgets();
}

void UTowerDefenceHudWidget::AddHealth(const uint32 HealthOrbCount) const
{
	if (!ResourceWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("TowerDefenceHud is missing referance to ResourceWidget"));
		return;
	}
	
	ResourceWidget->AddHealthOrbWidgets(HealthOrbCount);
}
