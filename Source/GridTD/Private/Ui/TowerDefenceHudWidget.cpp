// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/TowerDefenceHudWidget.h"

#include "TurretSocket.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Ui/PlayerResourceWidget.h"
#include "Ui/RadialSelectionWidget.h"
#include "Ui/ErrorDisplayWidget.h"

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
	if (TurretBuildWidget)
	{
		TurretBuildWidget->SetVisibility(ESlateVisibility::Collapsed);

		// I dont like the way this is done but currently not sure how to do it otherwise. Its dynamic so can't use lambda
		// Setup turret build buttons
		TurretBuildWidget->TopLeftButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::BuildGunTurret);
		TurretBuildWidget->TopRightButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::BuildCannonTurret);
		TurretBuildWidget->LeftButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::BuildRocketTurret);
		TurretBuildWidget->RightButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::BuildPiercingTurret);
		TurretBuildWidget->BottomLeftButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::BuildSlowTurret);
		TurretBuildWidget->BottomRightButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::BuildBuffTurret);
	}

	if (TurretSelectedWidget)
	{
		TurretSelectedWidget->SetVisibility(ESlateVisibility::Collapsed);

		// Setup turret selected buttons
		TurretSelectedWidget->LeftButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::UpgradeTurret);
		TurretSelectedWidget->RightButton->OnClicked.AddDynamic(this, &UTowerDefenceHudWidget::SellTurret);
	}

	if (ErrorDisplayWidget)
	{
		ErrorDisplayWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UTowerDefenceHudWidget::BuildGunTurret()
{
	TurretButtonClickedEvent.Broadcast(TurretGun);
	CloseTurretBuildWidget();
}

void UTowerDefenceHudWidget::BuildCannonTurret()
{
	TurretButtonClickedEvent.Broadcast(TurretCannon);
	CloseTurretBuildWidget();
}

void UTowerDefenceHudWidget::BuildRocketTurret()
{
	TurretButtonClickedEvent.Broadcast(TurretRocket);
	CloseTurretBuildWidget();
}

void UTowerDefenceHudWidget::BuildPiercingTurret()
{
	TurretButtonClickedEvent.Broadcast(TurretPiercing);
	CloseTurretBuildWidget();
}

void UTowerDefenceHudWidget::BuildSlowTurret()
{
	TurretButtonClickedEvent.Broadcast(TurretSlow);
	CloseTurretBuildWidget();
}

void UTowerDefenceHudWidget::BuildBuffTurret()
{
	TurretButtonClickedEvent.Broadcast(TurretBuff);
	CloseTurretBuildWidget();
}

void UTowerDefenceHudWidget::UpgradeTurret()
{
	TurretSelectionButtonClickedEvent.Broadcast(TurretSelectionUpgrade);
	CloseTurretSelectionWidget();
}

void UTowerDefenceHudWidget::SellTurret()
{
	TurretSelectionButtonClickedEvent.Broadcast(TurretSelectionSell);
	CloseTurretSelectionWidget();
}

void UTowerDefenceHudWidget::AddTurretButtonClickedEvent(const FScriptDelegate& Delegate)
{
	TurretButtonClickedEvent.Add(Delegate);
}

void UTowerDefenceHudWidget::AddTurretSelectionButtonClickedEvent(const FScriptDelegate& Delegate)
{
	TurretSelectionButtonClickedEvent.Add(Delegate);
}

void UTowerDefenceHudWidget::SelectTurretSocket(const ATurretSocket* TurretSocket)
{
	if (!TurretSocket) return;

	// Open to corresponding menu
	if (TurretSocket->HasTurret())
	{
		// Disable upgrade button if turret is max level
		TurretSelectedWidget->LeftButton->SetIsEnabled(!TurretSocket->IsTurretMaxLevel());

		// Used to move the selection widget to the correct location
		OpenTurretSelectionMenuEvent();
	}
	else
	{
		// Used to move the build widget to the correct location
		OpenTurretBuildMenuEvent();
	}
}

void UTowerDefenceHudWidget::CloseTurretBuildWidget() const
{
	if (!TurretBuildWidget) return;
	TurretBuildWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UTowerDefenceHudWidget::CloseTurretSelectionWidget() const
{
	if (!TurretSelectedWidget) return;
	TurretSelectedWidget->SetVisibility(ESlateVisibility::Collapsed);
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

void UTowerDefenceHudWidget::DisplayError(const FText& ErrorMessage)
{
	NULLCHECK(ErrorDisplayWidget, "TowerDefenceHud is missing referance to ErrorDisplayWidget");
	
	ErrorDisplayWidget->SetErrorText(ErrorMessage);
	ErrorDisplayWidget->SetVisibility(ESlateVisibility::Visible);

	if (GetWorld()->GetTimerManager().IsTimerActive(ErrorDisplayTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(ErrorDisplayTimerHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(ErrorDisplayTimerHandle, this, &UTowerDefenceHudWidget::HideErrorMessage, ErrorMessageDisplayTime, false);
}

void UTowerDefenceHudWidget::HideErrorMessage() const
{
	NULLCHECK(ErrorDisplayWidget, "TowerDefenceHud is missing referance to ErrorDisplayWidget");
	
	ErrorDisplayWidget->SetVisibility(ESlateVisibility::Collapsed);
}
