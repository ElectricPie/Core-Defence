// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/TowerDefenceHudWidget.h"

#include "Turret.h"
#include "TurretSocket.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "DataAssets/TurretDataAsset.h"
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

// TODO: Think I need to move this to the player controller as it need to update resources. Might be an idea to use
// TODO: enums for the different states of the turret selection widget.
void UTowerDefenceHudWidget::SetUpWidgets() const
{
	if (TurretSelectionWidget)
	{
		TurretSelectionWidget->SetVisibility(ESlateVisibility::Collapsed);

		// TODO: I dont like the way this is done but currently not sure how to do it otherwise. Its dynamic so can't use
		//   lambda
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
	if (!TurretSelectionWidget || !GunTurretBlueprint || !SelectedTurretSocket || !OwningPlayer) return;
	SelectedTurretSocket->AddTurret(GunTurretBlueprint, OwningPlayer);
}

void UTowerDefenceHudWidget::BuildCannonTurret()
{
	if (!TurretSelectionWidget || !CannonTurretBlueprint || !SelectedTurretSocket || !OwningPlayer)  return;
	SelectedTurretSocket->AddTurret(CannonTurretBlueprint, OwningPlayer);
}

void UTowerDefenceHudWidget::BuildRocketTurret()
{
	if (!TurretSelectionWidget || !RocketTurretBlueprint || !SelectedTurretSocket || !OwningPlayer)  return;
	SelectedTurretSocket->AddTurret(RocketTurretBlueprint, OwningPlayer);
}

void UTowerDefenceHudWidget::BuildPiercingTurret()
{
	if (!TurretSelectionWidget || !PiercingTurretBlueprint || !SelectedTurretSocket || !OwningPlayer) return;
	SelectedTurretSocket->AddTurret(PiercingTurretBlueprint, OwningPlayer);
}

void UTowerDefenceHudWidget::BuildSlowTurret()
{
	if (!TurretSelectionWidget || !SlowTurretBlueprint || !SelectedTurretSocket || !OwningPlayer) return;
	SelectedTurretSocket->AddTurret(SlowTurretBlueprint, OwningPlayer);
}

void UTowerDefenceHudWidget::BuildBuffTurret()
{
	if (!TurretSelectionWidget || !BuffTurretBlueprint || !SelectedTurretSocket || !OwningPlayer) return;
	SelectedTurretSocket->AddTurret(BuffTurretBlueprint, OwningPlayer);
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
