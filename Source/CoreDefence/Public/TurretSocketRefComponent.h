// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretSocket.h"
#include "Components/ActorComponent.h"
#include "TurretSocketRefComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COREDEFENCE_API UTurretSocketRefComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTurretSocketRefComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(VisibleAnywhere)
	ATurretSocket* OwningSocket;
	
public:
	void SetTurretSocket(ATurretSocket* TurretSocket) { OwningSocket = TurretSocket; }
	ATurretSocket* GetTurretSocket() const { return OwningSocket; }
};
