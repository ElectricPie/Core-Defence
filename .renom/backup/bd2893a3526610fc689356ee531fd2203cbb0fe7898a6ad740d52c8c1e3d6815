// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ErrorDisplayWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class GRIDTD_API UErrorDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category="Widgets", meta=(BindWidget))
	UTextBlock* ErrorTextWidget;

public:
	UFUNCTION(BlueprintCallable)
	void SetErrorText(const FText& ErrorText);
};
