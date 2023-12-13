// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerResourceWidget.generated.h"

class UTextBlock;
class UGridPanel;
class UHealthOrbWidget;
/**
 * 
 */
UCLASS()
class GRIDTD_API UPlayerResourceWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	TArray<UHealthOrbWidget*> HealthGrid;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resources")
	UTextBlock* ResourcesValueWidget;

	UPROPERTY(EditAnywhere, Category="Health")
	uint8 DebugAmount;
	UPROPERTY(EditAnywhere, Category="Health")
	TSubclassOf<UHealthOrbWidget> HealthOrbBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	UGridPanel* HealthGridWidget;
	UPROPERTY(EditAnywhere, Category="Health")
	uint8 GridColumns = 0.f;
	UPROPERTY(EditAnywhere, Category="Health")
	uint8 GridRows = 0.f;
	UPROPERTY(EditAnywhere, Category="Health")
	float GridPadding = 1.f;

	void GenerateHealthOrbWidgets(uint16 HealthOrbCount);

	void ClearOrbWidgets();
};
