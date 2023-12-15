// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/PlayerResourceWidget.h"

#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Ui/HealthOrbWidget.h"

// TODO: Remove after testing
void UPlayerResourceWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerResourceWidget::AddHealthOrbWidgets(uint32 HealthOrbCount)
{
	// Check if all references are valid
	if (!ResourcesValueWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerResource Widget is missing referance to 'ResourcesValueWidget'") );
		return;
	}
	if (!HealthGridWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerResource Widget is missing referance to 'HealthGridWidget'") );
		return;
	}
	if (!HealthOrbBlueprint)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerResource Widget is missing referance to 'HealthOrbBlueprint'") );
		return;
	}

	// Prevent the orbs from overfilling the grid
	const uint32 GridCurrentSize = HealthGrid.Num();
	const uint32 FreeSlots = GridCurrentSize + GridColumns * GridRows;
	if (HealthOrbCount > FreeSlots)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to add more orbs (%d) than available positions (%d: %dx%d) PlayerResource widget"), HealthOrbCount, FreeSlots, GridColumns, GridRows);
		HealthOrbCount = FreeSlots;
	}

	for (uint32 i = GridCurrentSize; i < HealthOrbCount + GridCurrentSize; i++)
	{
		const uint32 Column = i % GridColumns;
		const uint32 Row = i / GridColumns;
		
		UHealthOrbWidget* NewHealthWidget = CreateWidget<UHealthOrbWidget>(GetWorld(), HealthOrbBlueprint);

		// Add widget to grid
		UGridSlot* GridSlot = HealthGridWidget->AddChildToGrid(NewHealthWidget);
		GridSlot->SetColumn(Column);
		GridSlot->SetRow(Row);
		GridSlot->SetPadding(GridPadding);
		// TODO: Add nudging by half the heath widgets size

		HealthGrid.Add(NewHealthWidget);
	}
}

void UPlayerResourceWidget::AddHealthOrbWidget()
{
}

void UPlayerResourceWidget::ClearOrbWidgets()
{
	HealthGridWidget->ClearChildren();
	HealthGrid.Empty();
}
