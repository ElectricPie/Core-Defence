// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BirdsEyePlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCapsuleComponent;

UCLASS()
class GRIDTD_API ABirdsEyePlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABirdsEyePlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;


private:
	UPROPERTY(EditAnywhere, Category = "Inputs", meta = (AllowPrivateAccess = true))
	float SpeedModifier = 1000.f;

	FVector CurrentVelocity;
	
	void MoveXAxis(float Value);
	void MoveYAxis(float Value);
};
