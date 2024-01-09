// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/ErrorDisplayWidget.h"

#include "Components/TextBlock.h"

void UErrorDisplayWidget::SetErrorText(const FText& ErrorText)
{
	if (!ErrorTextWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("ErrorDisplayWidget: ErrorTextWidget is nullptr"));
		return;
	}

	ErrorTextWidget->SetText(ErrorText);
}
