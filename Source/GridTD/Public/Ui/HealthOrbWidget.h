// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthOrbWidget.generated.h"

class UImage;

UENUM(BlueprintType)
enum EOrbState
{
	Stored,
	Taken,
	Lost
};

/**
 * 
 */
UCLASS()
class GRIDTD_API UHealthOrbWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	UImage* OrbImage;

	UPROPERTY(EditAnywhere, Category="Orb State")
	FLinearColor StoreColor = FLinearColor::Green;
	UPROPERTY(EditAnywhere, Category="Orb State")
	FLinearColor TakenColor = FLinearColor::Red;
	UPROPERTY(EditAnywhere, Category="Orb State")
	FLinearColor LostColor = FLinearColor::Black;
	
public:
	UFUNCTION(BlueprintCallable)
	void SetState(const EOrbState State) const;
};
