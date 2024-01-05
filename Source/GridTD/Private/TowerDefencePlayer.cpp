// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefencePlayer.h"

#include "EngineUtils.h"
#include "Turret.h"
#include "Health/HealthPoint.h"
#include "TurretSocket.h"
#include "TurretSocketRefComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/LevelSettings.h"
#include "Ui/TowerDefenceHudWidget.h"
#include "Enums/ETurretType.h"
#include "Enums/ETurretBuildErrors.h"

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

	// TODO: Get socket if selected turret
	if (const UTurretSocketRefComponent* SocketRef = Cast<UTurretSocketRefComponent>(HitActor->GetComponentByClass(UTurretSocketRefComponent::StaticClass())))
	{
		UE_LOG(LogTemp, Warning, TEXT("SocketRef: %s"), *SocketRef->GetTurretSocket()->GetName());
	}
	
	SelectedTurretSocket = Cast<ATurretSocket>(HitActor);
	if (!SelectedTurretSocket) return;
	
	HudWidget->SelectTurretSocket(SelectedTurretSocket);
}

void ATowerDefencePlayer::SetupUi()
{
	if (!HudWidgetBlueprint) return;
	HudWidget = CreateWidget<UTowerDefenceHudWidget>(GetWorld(), HudWidgetBlueprint);
	HudWidget->AddToViewport();
	HudWidget->UpdateResources(Resources);

	FScriptDelegate TurretBuildDelegate;
	TurretBuildDelegate.BindUFunction(this, FName("OnTurretToBuildSelected"));
	HudWidget->AddTurretButtonClickedEvent(TurretBuildDelegate);
}

void ATowerDefencePlayer::OnOrbStateChanged(const EHealthOrbState OrbState)
{
	UE_LOG(LogTemp, Warning, TEXT("OrbState"));
	HudWidget->ChangeOrbState(OrbState);
}

void ATowerDefencePlayer::OnTurretToBuildSelected(ETurretType TurretType)
{
	if (!SelectedTurretSocket) return;
	if (SelectedTurretSocket->HasTurret()) return;

	ETurretBuildErrors BuildError = Success;
	
	// Build the corresponding turret
	switch (TurretType)
	{
		case Gun:
			BuildError = SelectedTurretSocket->BuildTurret(GunTurretBlueprint, this);
			break;
		case Cannon:
			BuildError = SelectedTurretSocket->BuildTurret(CannonTurretBlueprint, this);
			break;
		case Rocket:
			BuildError = SelectedTurretSocket->BuildTurret(RocketTurretBlueprint, this);
			break;
		case Piercing:
			BuildError = SelectedTurretSocket->BuildTurret(PiercingTurretBlueprint, this);
			break;
		case Slow:
			BuildError = SelectedTurretSocket->BuildTurret(SlowTurretBlueprint, this);
			break;
		case Buff:
			BuildError = SelectedTurretSocket->BuildTurret(BuffTurretBlueprint, this);
			break;
		default:
			break;
	}

	// Handle turret build errors
	switch (BuildError)
	{
		case SocketOccupied:
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to assign turret to occupied turret socket"));
			break;
		case NotEnoughResources:
			if (!HudWidget)
			{
				UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Has no HudWidget"));
				break;
			}
			HudWidget->DisplayError(InsufficientResourcesText);
			break;
		case NullDataAsset:
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to build turret with null data asset"));
			break;
		case NullPlayerReference:
			UE_LOG(LogTemp, Error, TEXT("TowerDefencePlayer: Attempted to assign turret with null player"));
			break;
		case Success:
			break;
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
	HudWidget->UpdateResources(Resources);
	
	return true;
}
