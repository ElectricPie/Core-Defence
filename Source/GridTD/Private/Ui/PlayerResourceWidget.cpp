// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/PlayerResourceWidget.h"

#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Ui/HealthOrbWidget.h"

// TODO: Remove after testing
void UPlayerResourceWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	GenerateHealthOrbWidgets(DebugAmount);
}

void UPlayerResourceWidget::GenerateHealthOrbWidgets(uint16 HealthOrbCount)
{
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
	const int16 TotalSlots = GridColumns * GridRows;
	if (HealthOrbCount > TotalSlots)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to add more orbs (%d) than available positions (%d: %dx%d) PlayerResource widget"), HealthOrbCount, TotalSlots, GridColumns, GridRows);
		HealthOrbCount = TotalSlots;
	}

	for (uint8 i = 0; i < HealthOrbCount; i++)
	{
		const uint8 Column = i % GridColumns;
		const uint8 Row = i / GridColumns;
		
		// Create new Health Orb widget
		UHealthOrbWidget* NewHealthWidget = CreateWidget<UHealthOrbWidget>(GetWorld(), HealthOrbBlueprint);

		// Add widget to grid
		UGridSlot* GridSlot = HealthGridWidget->AddChildToGrid(NewHealthWidget);
		GridSlot->SetColumn(Column);
		GridSlot->SetRow(Row);
		GridSlot->SetPadding(GridPadding);
	}
}
