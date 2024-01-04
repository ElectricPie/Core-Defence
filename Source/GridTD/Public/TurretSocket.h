// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretSocket.generated.h"

class ATurret;
class ATowerDefencePlayer;

UCLASS()
class GRIDTD_API ATurretSocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretSocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void BuildTurret(const UTurretDataAsset* TurretDataAsset, ATowerDefencePlayer*  OwningPlayer);

	/**
	 * Checks if the socket contains a turret
	 * @return True if the socket has a turret
	 */
	bool HasTurret() const;

private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, Category="Components")
	USceneComponent* Socket;
	UPROPERTY()
	ATurret* TurretInSocket;
};
