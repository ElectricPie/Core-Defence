// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefencePlayer.h"

#include "EngineUtils.h"
#include "Health/HealthPoint.h"
#include "TurretSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/LevelSettings.h"
#include "Ui/TowerDefenceHudWidget.h"
#include "Enums/ETurretType.h"


void ATowerDefencePlayer::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	
	UWorld* World = GetWorld();
	if (!World) return;

	// Get Settings from settings actor
	const ALevelSettings* LevelSettings = Cast<ALevelSettings>(UGameplayStatics::GetActorOfClass(World, ALevelSettings::StaticClass()));
	if (LevelSettings)
	{
		Resources = LevelSettings->GetPlayerStartingResources();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No LevelSettings actor found in the world, using default values"));
	}

	SetupUi();

	// Get all health points and update the Hud
	for (AHealthPoint* HealthPoint : TActorRange<AHealthPoint>(World))
	{
		const uint32 AdditionalHealth = HealthPoint->GetOrbCount();
		HudWidget->AddHealth(AdditionalHealth);
		
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
	HudWidget->CloseTurretSelectionWidget();
	
	// Get the screen position of the mouse
	FVector2D MouseScreenPos;
	if (!GetMouseScreenPos(MouseScreenPos)) return;
	
	FVector HitLocation;
	AActor* HitActor = nullptr;
	if (!RaycastToMouse(MouseScreenPos, HitLocation, HitActor)) return;

	SelectedTurretSocket = Cast<ATurretSocket>(HitActor);
	if (!SelectedTurretSocket) return;

	if (SelectedTurretSocket->HasTurret())
	{
		// TODO: Handle turret upgrades and displays
	}
	else
	{
		HudWidget->SelectTurretSocket(SelectedTurretSocket);
	}
}

void ATowerDefencePlayer::SetupUi()
{
	if (!HudWidgetBlueprint) return;
	HudWidget = CreateWidget<UTowerDefenceHudWidget>(GetWorld(), HudWidgetBlueprint);
	HudWidget->AddToViewport();
	HudWidget->UpdateResources(Resources);
	HudWidget->TurretButtonClickedEvent.AddDynamic(this, &ATowerDefencePlayer::OnTurretToBuildSelected);
}

void ATowerDefencePlayer::OnOrbStateChanged(const EHealthOrbState OrbState)
{
	UE_LOG(LogTemp, Warning, TEXT("OrbState"));
	HudWidget->ChangeOrbState(OrbState);
}

void ATowerDefencePlayer::OnTurretToBuildSelected(ETurretType TurretType)
{
	switch (TurretType)
	{
		case Gun:
			UE_LOG(LogTemp, Warning, TEXT("Gun"));
			break;
		case Cannon:
			UE_LOG(LogTemp, Warning, TEXT("Canon"));
			break;
		case Rocket:
			UE_LOG(LogTemp, Warning, TEXT("Rocket"));
			break;
		case Piercing:
			UE_LOG(LogTemp, Warning, TEXT("Piercing"));
			break;
		case Slow:
			UE_LOG(LogTemp, Warning, TEXT("Slow"));
			break;
		case Buff:
			UE_LOG(LogTemp, Warning, TEXT("Buff"));
			break;
		default:
			break;
	}
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
