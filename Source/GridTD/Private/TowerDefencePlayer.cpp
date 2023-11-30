// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefencePlayer.h"

#include "Ui/TowerDefenceHudWidget.h"


void ATowerDefencePlayer::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	SetupUi();
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
	FVector HitLocation;
	AActor* HitActor = nullptr;
	if (RaycastToMouse(HitLocation, HitActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s, %s"), *HitActor->GetActorLabel(), *HitLocation.ToString());
	}
}

void ATowerDefencePlayer::SetupUi()
{
	if (!HudWidgetBlueprint) return;
	HudWidget = CreateWidget<UTowerDefenceHudWidget>(GetWorld(), HudWidgetBlueprint);
	HudWidget->AddToViewport();
}

bool ATowerDefencePlayer::RaycastToMouse(FVector& HitLocation, AActor*& HitActor)
{
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D MouseScreenLocation;
	
	// Get the screen position of the mouse
	if (GetMousePosition(MouseScreenLocation.X, MouseScreenLocation.Y))
	{
		// Get the direction of the mouse
		FVector WorldPosition;
		FVector WorldDirection;
		DeprojectScreenPositionToWorld(MouseScreenLocation.X, MouseScreenLocation.Y, WorldPosition, WorldDirection);
	
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
	}

	return false;
}

void ATowerDefencePlayer::RegisterPlayerHealth(int32 AdditionalHealth)
{
	MaxHealth += AdditionalHealth;
	Health += AdditionalHealth;
}

void ATowerDefencePlayer::ReduceHealth()
{
	Health--;

	if (Health > 0) return;
	GameOver();
}
