// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BirdsEyePlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABirdsEyePlayerCharacter::ABirdsEyePlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsual"));
	RootComponent = CapsuleComponent;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
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

	FVector NewPos = GetActorLocation() + CurrentVelocity * DeltaTime;
	SetActorLocation(NewPos);
}

// Called to bind functionality to input
void ABirdsEyePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveXAxis", this, &ABirdsEyePlayerCharacter::MoveXAxis);
	PlayerInputComponent->BindAxis("MoveYAxis", this, &ABirdsEyePlayerCharacter::MoveYAxis);
}

void ABirdsEyePlayerCharacter::MoveXAxis(float Value)
{
	CurrentVelocity.X = FMath::Clamp(Value, -1.f, 1.f) * SpeedModifier;
} 

void ABirdsEyePlayerCharacter::MoveYAxis(float Value)
{
	CurrentVelocity.Y = FMath::Clamp(Value, -1.f, 1.f) * SpeedModifier;
}

