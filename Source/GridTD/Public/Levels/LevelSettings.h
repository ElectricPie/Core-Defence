// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSettings.generated.h"

UCLASS()
class GRIDTD_API ALevelSettings : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelSettings();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Player Settings", meta=(AllowPrivateAccess = "true"))
	int32 PlayerStartingResources = 100;

public:
	UFUNCTION(BlueprintPure)
	int32 GetPlayerStartingResources() const { return PlayerStartingResources; }
};
