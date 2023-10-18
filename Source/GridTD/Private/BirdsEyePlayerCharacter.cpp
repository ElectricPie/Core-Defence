// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdsEyePlayerCharacter.h"

// Sets default values
ABirdsEyePlayerCharacter::ABirdsEyePlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABirdsEyePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABirdsEyePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABirdsEyePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

