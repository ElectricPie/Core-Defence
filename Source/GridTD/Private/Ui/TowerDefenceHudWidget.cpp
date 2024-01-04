// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/TowerDefenceHudWidget.h"

#include "TurretSocket.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Ui/PlayerResourceWidget.h"
#include "Ui/RadialSelectionWidget.h"

#define NULLCHECK(Pointer, ErrorMessage) if (!Pointer) \
{ \
UE_LOG(LogTemp, Warning, TEXT(ErrorMessage)); \
return; \
}

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

		// I dont like the way this is done but currently not sure how to do it otherwise. Its dynamic so can't use lambda
		TurretSelectionWidget->TopLeftButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::BuildGunTurret);
		TurretSelectionWidget->TopRightButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::BuildCannonTurret);
		TurretSelectionWidget->LeftButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::BuildRocketTurret);
		TurretSelectionWidget->RightButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::BuildPiercingTurret);
		TurretSelectionWidget->BottomLeftButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::BuildSlowTurret);
		TurretSelectionWidget->BottomRightButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::BuildBuffTurret);
	}
}

void UTowerDefenceHudWidget::BuildGunTurret()
{
	TurretButtonClickedEvent.Broadcast(Gun);
}

void UTowerDefenceHudWidget::BuildCannonTurret()
{
	TurretButtonClickedEvent.Broadcast(Cannon);
}

void UTowerDefenceHudWidget::BuildRocketTurret()
{
	TurretButtonClickedEvent.Broadcast(Rocket);
}

void UTowerDefenceHudWidget::BuildPiercingTurret()
{
	TurretButtonClickedEvent.Broadcast(Piercing);
}

void UTowerDefenceHudWidget::BuildSlowTurret()
{
	TurretButtonClickedEvent.Broadcast(Slow);
}

void UTowerDefenceHudWidget::BuildBuffTurret()
{
	TurretButtonClickedEvent.Broadcast(Buff);
}

void UTowerDefenceHudWidget::AddTurretButtonClickedEvent(const FScriptDelegate& Delegate)
{
	TurretButtonClickedEvent.Add(Delegate);
}

void UTowerDefenceHudWidget::SelectTurretSocket(ATurretSocket* TurretSocket)
{
	SelectedTurretSocket = TurretSocket;
	SelectedTurretEvent();
}

void UTowerDefenceHudWidget::CloseTurretSelectionWidget() const
{
	if (!TurretSelectionWidget) return;
	TurretSelectionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UTowerDefenceHudWidget::ClearHealth() const
{
	NULLCHECK(ResourceWidget, "TowerDefenceHud is missing referance to ResourceWidget");
	
	ResourceWidget->ClearOrbWidgets();
}

void UTowerDefenceHudWidget::AddHealth(const uint32 HealthOrbCount) const
{
	NULLCHECK(ResourceWidget, "TowerDefenceHud is missing referance to ResourceWidget");
	
	ResourceWidget->AddHealthOrbWidgets(HealthOrbCount);
}

void UTowerDefenceHudWidget::ChangeOrbState(const EHealthOrbState OrbState)
{
	NULLCHECK(ResourceWidget, "TowerDefenceHud is missing referance to ResourceWidget");
	
	ResourceWidget->ChangeOrbState(OrbState);
}

void UTowerDefenceHudWidget::UpdateResources(const int32 Value) const
{
	NULLCHECK(ResourceWidget, "TowerDefenceHud is missing referance to ResourceWidget");

	ResourceWidget->UpdateResourceValue(Value);
}
