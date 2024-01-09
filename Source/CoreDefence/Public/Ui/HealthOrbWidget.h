// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Health/HealthOrbState.h"
#include "HealthOrbWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class COREDEFENCE_API UHealthOrbWidget : public UUserWidget
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
	UFUNCTION()
	void SetState(const EHealthOrbState State);
};
