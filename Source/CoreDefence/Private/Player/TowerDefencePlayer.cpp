// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TowerDefencePlayer.h"

#include "EngineUtils.h"
#include "Health/HealthPoint.h"
#include "Turrets/TurretSocket.h"
#include "Turrets/TurretSocketRefComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/LevelSettings.h"
#include "Ui/TowerDefenceHudWidget.h"
#include "Ui/PlayerResourceWidget.h"
#include "Enums/ETurretType.h"
#include "Enums/ETurretBuildErrors.h"
#include "Enums/ETurretSelectionOption.h"

void ATowerDefencePlayer::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	
	UWorld* World = GetWorld();
	if (!World) return;

	// Get Settings from settings actor
	LevelSettings = Cast<ALevelSettings>(UGameplayStatics::GetActorOfClass(World, ALevelSettings::StaticClass()));
	if (LevelSettings)
	{
		Resources = LevelSettings->GetPlayerStartingResources();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No LevelSettings actor found in the world, using default values"));
	}

	SetupUi();

	if (!ResourceWidget) return;
	
	// Get all health points and update the Hud
	for (AHealthPoint* HealthPoint : TActorRange<AHealthPoint>(World))
	{
		const uint32 AdditionalHealth = HealthPoint->GetOrbCount();
		
		ResourceWidget->AddHealthOrbWidgets(AdditionalHealth);
		
		MaxHealth += AdditionalHealth;
		Health += AdditionalHealth;

		HealthPoint->OrbStateChangedEvent.AddDynamic(this, &ATowerDefencePlayer::OnOrbStateChanged);
	}
}


void ATowerDefencePlayer::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Select", IE_Pressed, this, &ATowerDefencePlayer::Select);
}

void ATowerDefencePlayer::GameOver_Implementation()
{
}


void ATowerDefencePlayer::Select()
{
	if (!HudWidget) return;
	HudWidget->CloseTurretBuildWidget();
	
	// Get the screen position of the mouse
	FVector2D MouseScreenPos;
	if (!GetMouseScreenPos(MouseScreenPos)) return;
	
	FVector HitLocation;
	AActor* HitActor = nullptr;
	if (!RaycastToMouse(MouseScreenPos, HitLocation, HitActor)) return;

	// Get the turret socket
	SelectedTurretSocket = Cast<ATurretSocket>(HitActor);
	if (!SelectedTurretSocket)
	{
		// Check for socket ref component if we don't get a socket
		if (const UTurretSocketRefComponent* SocketRef = Cast<UTurretSocketRefComponent>(HitActor->GetComponentByClass(UTurretSocketRefComponent::StaticClass())))
		{
			SelectedTurretSocket = SocketRef->GetTurretSocket();

			// If the socket ref component is null, we have a problem
			if (!SelectedTurretSocket) return;
		}
	}
	
	HudWidget->SelectTurretSocket(SelectedTurretSocket);
}

void ATowerDefencePlayer::SetupUi()
{
	if (!HudWidgetBlueprint) return;
	HudWidget = CreateWidget<UTowerDefenceHudWidget>(GetWorld(), HudWidgetBlueprint);
	HudWidget->AddToViewport();
	ResourceWidget = HudWidget->GetResourceWidget();
	if (ResourceWidget) {
		ResourceWidget->UpdateResourceValue(Resources);
	}

	FScriptDelegate TurretBuildDelegate;
	TurretBuildDelegate.BindUFunction(this, FName("OnTurretToBuildSelected"));
	HudWidget->AddTurretButtonClickedEvent(TurretBuildDelegate);

	FScriptDelegate TurretSelectionDelegate;
	TurretSelectionDelegate.BindUFunction(this, FName("OnTurretSelectionOptionSelected"));
	HudWidget->AddTurretSelectionButtonClickedEvent(TurretSelectionDelegate);
	
}

void ATowerDefencePlayer::OnOrbStateChanged(const EHealthOrbState OrbState)
{
	UE_LOG(LogTemp, Warning, TEXT("OrbState"));
	
	if (!ResourceWidget) return;
	ResourceWidget->ChangeOrbState(OrbState);
}

void ATowerDefencePlayer::OnTurretToBuildSelected(const ETurretType TurretType)
{
	if (!SelectedTurretSocket) return;
	if (SelectedTurretSocket->HasTurret()) return;

	ETurretBuildErrors BuildError = TurretBuildSuccess;
	
	// Build the corresponding turret
	switch (TurretType)
	{
		case TurretGun:
			BuildError = SelectedTurretSocket->BuildTurret(GunTurretUpgradeDataAsset, this);
			break;
		case TurretCannon:
			BuildError = SelectedTurretSocket->BuildTurret(CannonTurretUpgradeDataAsset, this);
			break;
		case TurretRocket:
			BuildError = SelectedTurretSocket->BuildTurret(RocketTurretUpgradeDataAsset, this);
			break;
		case TurretPiercing:
			BuildError = SelectedTurretSocket->BuildTurret(PiercingTurretUpgradeDataAsset, this);
			break;
		case TurretSlow:
			BuildError = SelectedTurretSocket->BuildTurret(SlowTurretUpgradeDataAsset, this);
			break;
		case TurretBuff:
			BuildError = SelectedTurretSocket->BuildTurret(BuffTurretUpgradeDataAsset, this);
			break;
		default:
			break;
	}

	// Handle turret build errors
	switch (BuildError)
	{
		case TurretBuildSocketOccupied:
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to assign turret to occupied turret socket"));
			break;
		case TurretBuildNotEnoughResources:
			if (!HudWidget)
			{
				UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Has no HudWidget"));
				break;
			}
			HudWidget->DisplayError(InsufficientResourcesText);
			break;
		case TurretBuildNullDataAsset:
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to build turret with null data asset"));
			break;
		case TurretBuildNullPlayerReference:
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to assign turret with null player"));
			break;
		case TurretBuildSuccess:
			break;
		case TurretBuildNullUpgradePath: 
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to build turret with null upgrade path"));
			break;
		case TurretBuildEmptyUpgradePath:
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to build turret with empty upgrade path"));
			break;
		default:
			break;
	}

	// Clear the selected turret socket
	SelectedTurretSocket = nullptr;
}

void ATowerDefencePlayer::HandleUpgradeError(const ETurretUpgradeErrors UpgradeError)
{
	switch (UpgradeError) {
		case TurretUpgradeNotEnoughResources:
			// TODO: Display error message
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Not enough resources to upgrade turret"));
			break;
		case TurretUpgradeEndOfUpgradePath:
			// This should not happen as the upgrade button should be disabled
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to upgrade turret at end of upgrade path"));
			break;
		case TurretUpgradeNoTurretInSocket:
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to upgrade turret in socket with no turret"));
			break;
		case TurretUpgradeNullUpgradePath:
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to upgrade turret with null upgrade path"));
			break;
		case TurretUpgradeNullPlayerReference:
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to upgrade turret with null player"));
			break;
		case TurretUpgradeNullDataAsset:
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to upgrade turret with null data asset"));
			break;
		case TurretUpgradeSuccess:
			break;
		default: ;
	}
}

void ATowerDefencePlayer::OnTurretSelectionOptionSelected(const ETurretSelectionOption TurretSelectionOption)
{
	if (!SelectedTurretSocket) return;
	if (!SelectedTurretSocket->HasTurret()) return;

	switch (TurretSelectionOption)
	{
		case TurretSelectionUpgrade:
			{
				const ETurretUpgradeErrors UpgradeError = SelectedTurretSocket->UpgradeTurret(this);
				HandleUpgradeError(UpgradeError);
				break;
			}
		case TurretSelectionSell:
			{
				float RefundPercent = 1.f;
				if (LevelSettings)
				{
					RefundPercent = LevelSettings->GetTurretSellRefundPercentage();
				}
				SelectedTurretSocket->SellTurret(RefundPercent);
				break;
			}
		default:
			break;
	}

	// Clear the selected turret socket
	SelectedTurretSocket = nullptr;
}

bool ATowerDefencePlayer::GetMouseScreenPos(FVector2D& MouseScreenPos) const
{
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Get the screen position of the mouse
	return GetMousePosition(MouseScreenPos.X, MouseScreenPos.Y);
}

bool ATowerDefencePlayer::RaycastToMouse(const FVector2D& MouseScreenPos, FVector& HitLocation, AActor*& HitActor) const
{
	// Get the direction of the mouse
	FVector WorldPosition;
	FVector WorldDirection;
	DeprojectScreenPositionToWorld(MouseScreenPos.X, MouseScreenPos.Y, WorldPosition, WorldDirection);
	
	// Raycast
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldPosition,
	WorldPosition + WorldDirection * SelectionRaycastDistance, ECC_Visibility, QueryParams))
	{
		HitActor = HitResult.GetActor();
		HitLocation = HitResult.ImpactPoint;
		return true;
	}

	return false;
}

void ATowerDefencePlayer::ReduceHealth()
{
	Health--;

	if (Health > 0) return;
	GameOver();
}

bool ATowerDefencePlayer::RemoveResources(const int32 Amount)
{
	// Prevent negative resources
	if (Resources < Amount) return false;
	
	Resources -= Amount;
	if (ResourceWidget)
	{
		ResourceWidget->UpdateResourceValue(Resources);		
	}
	
	return true;
}

void ATowerDefencePlayer::AddResources(const int32 Amount)
{
	Resources += Amount;
	if (ResourceWidget)
	{
		ResourceWidget->UpdateResourceValue(Resources);		
	}
}
