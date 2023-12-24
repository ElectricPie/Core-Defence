// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/TowerDefenceHudWidget.h"

#include "Turret.h"
#include "TurretSocket.h"
#include "Components/Button.h"
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

		// I dont like the way this is done but currently not sure how to do it otherwise. Its dynamic so can't use
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
	if (!TurretSelectionWidget || !GunTurretBlueprint || !SelectedTurretSocket) return;
	SelectedTurretSocket->AddTurret(GunTurretBlueprint);
}

void UTowerDefenceHudWidget::BuildCannonTurret()
{
	if (!TurretSelectionWidget || !GunTurretBlueprint || !SelectedTurretSocket)  return;
	SelectedTurretSocket->AddTurret(CannonTurretBlueprint);
}

void UTowerDefenceHudWidget::BuildRocketTurret()
{
	if (!TurretSelectionWidget || !GunTurretBlueprint || !SelectedTurretSocket)  return;
	SelectedTurretSocket->AddTurret(RocketTurretBlueprint);
}

void UTowerDefenceHudWidget::BuildPiercingTurret()
{
	if (!TurretSelectionWidget || !GunTurretBlueprint || !SelectedTurretSocket) return;
	SelectedTurretSocket->AddTurret(PiercingTurretBlueprint);
}

void UTowerDefenceHudWidget::BuildSlowTurret()
{
	if (!TurretSelectionWidget || !GunTurretBlueprint || !SelectedTurretSocket)  return;
	SelectedTurretSocket->AddTurret(SlowTurretBlueprint);
}

void UTowerDefenceHudWidget::BuildBuffTurret()
{
	if (!TurretSelectionWidget || !GunTurretBlueprint || !SelectedTurretSocket)  return;
	SelectedTurretSocket->AddTurret(BuffTurretBlueprint);
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

void UTowerDefenceHudWidget::ChangeOrbState(const EHealthOrbState OrbState)
{
	ResourceWidget->ChangeOrbState(OrbState);
}
