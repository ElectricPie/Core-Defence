// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/PlayerResourceWidget.h"

#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/TextBlock.h"
#include "Ui/HealthOrbWidget.h"

void UPlayerResourceWidget::OrbStored()
{
}

void UPlayerResourceWidget::OrbTaken()
{
	if (TakenOrbCount + LostOrbCount >= HealthGrid.Num()) return;
	
	TakenOrbCount++;

	UHealthOrbWidget* t = HealthGrid[TakenOrbCount + LostOrbCount - 1];
	t->SetState(Taken);
}

void UPlayerResourceWidget::OrbLost()
{
	LostOrbCount++;
	HealthGrid[LostOrbCount - 1]->SetState(Lost);
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
		NewHealthWidget->SetState(Taken);
		
		// Add widget to grid
		UGridSlot* GridSlot = HealthGridWidget->AddChildToGrid(NewHealthWidget);
		GridSlot->SetColumn(Column);
		GridSlot->SetRow(Row);
		GridSlot->SetPadding(GridPadding);
		// TODO: Add nudging by half the heath widgets size

		// TODO: Fix issue with pointers not working in array or when assigned to other pointer
		HealthGrid.Push(NewHealthWidget);
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

void UPlayerResourceWidget::ChangeOrbState(const EHealthOrbState OrbState)
{
	// TODO:
	if (HealthGrid.Num() == 0) return;
	// UHealthOrbWidget* HealthOrbWidget = StoredOrbs.Pop();
	
	switch (OrbState)
	{
	case Stored:
		UE_LOG(LogTemp, Warning, TEXT("Stored"));
		OrbStored();
		break;
	case Taken:
		UE_LOG(LogTemp, Warning, TEXT("Taken"));
		OrbTaken();
		break;
	case Lost:
		UE_LOG(LogTemp, Warning, TEXT("Lost"));
		OrbLost();
		break;
	}
}

void UPlayerResourceWidget::UpdateResourceValue(const int32 Value) const
{
	if (!ResourcesValueWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerResource Widget is missing referance to 'ResourcesValueWidget'") );
		return;
	}

	ResourcesValueWidget->SetText(FText::FromString(FString::Printf(TEXT("%d"), Value)));
}
