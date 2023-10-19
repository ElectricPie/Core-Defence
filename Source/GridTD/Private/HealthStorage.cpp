// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthStorage.h"

#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UHealthStorage::UHealthStorage()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	if (GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner"));
		TriggerVolume->SetWorldLocation(GetOwner()->GetActorLocation());
	}
}


// Called when the game starts
void UHealthStorage::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &UHealthStorage::OnBeginOverlap);
}


// Called every frame
void UHealthStorage::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthStorage::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	
	UE_LOG(LogTemp, Warning, TEXT("Other Actor %s"), *OtherActor->GetActorLabel());
}
