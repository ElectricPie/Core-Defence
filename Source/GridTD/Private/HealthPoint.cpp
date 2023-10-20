// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPoint.h"

#include "TowerDefencePlayer.h"
#include "Components/BoxComponent.h"

// Sets default values
AHealthPoint::AHealthPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetCollisionProfileName(TEXT("IgnoreAll"));

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	TriggerVolume->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHealthPoint::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	TowerPlayerController = Cast<ATowerDefencePlayer>(GetWorld()->GetFirstPlayerController());
	if (!TowerPlayerController) return;
	TowerPlayerController->RegisterPlayerHealth(MaxHealth);
}

void AHealthPoint::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

// Called every frame
void AHealthPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

