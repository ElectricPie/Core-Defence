// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/TowerDefenceHudWidget.h"

void UTowerDefenceHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp,	Warning, TEXT("Boop 1"));
	SetUpWidgets();
}

void UTowerDefenceHudWidget::SetUpWidgets() const
{
	UE_LOG(LogTemp,	Warning, TEXT("Boop 2"));
	if (TurretSelectionWidget)
	{
		UE_LOG(LogTemp,	Warning, TEXT("Boop 3"));
		TurretSelectionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
