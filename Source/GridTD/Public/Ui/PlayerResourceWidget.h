// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Health/HealthOrbState.h"
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
	UPROPERTY()
	TArray<UHealthOrbWidget*> HealthGrid;

	int32 TakenOrbCount = 0;
	int32 LostOrbCount = 0;

	void OrbStored();
	void OrbTaken();
	void OrbLost();

protected:
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	UTextBlock* ResourcesValueWidget;
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	UGridPanel* HealthGridWidget;
	
public:
	UPROPERTY(EditAnywhere, Category="Health")
	uint8 DebugAmount;
	UPROPERTY(EditAnywhere, Category="Health")
	TSubclassOf<UHealthOrbWidget> HealthOrbBlueprint;
	UPROPERTY(EditAnywhere, Category="Health")
	uint8 GridColumns = 0.f;
	UPROPERTY(EditAnywhere, Category="Health")
	uint8 GridRows = 0.f;
	UPROPERTY(EditAnywhere, Category="Health")
	float GridPadding = 1.f;

	/**
	 * Creates the given number of HealthOrbWidgets and adds them to the resource grid
	 * @param HealthOrbCount The number of HealthOrbWidgets to be added
	 */
	void AddHealthOrbWidgets(uint32 HealthOrbCount);
	/**
	 * Creates a HealthOrbWidget and add it to the health grid
	 */
	void AddHealthOrbWidget();

	void ClearOrbWidgets();

	void ChangeOrbState(EHealthOrbState OrbState);

	void UpdateResourceValue(int32 Value) const;
};
