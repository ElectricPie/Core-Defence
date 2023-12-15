// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/HealthOrbWidget.h"
#include "Components/Image.h"

void UHealthOrbWidget::SetState(const EOrbState State) const
{
	if (!OrbImage)
	{
		UE_LOG(LogTemp, Error, TEXT("UHealthOrbWidget is missing referance to OrbImage"))
		return;
	}

	FLinearColor OrbColor;
	switch (State)
	{
	case Stored:
		OrbColor = StoreColor;
		break;
	case Taken:
		OrbColor = TakenColor;
		break;
	case Lost:
		OrbColor = LostColor;
		break;
	}

	OrbImage->ColorAndOpacity = OrbColor;
}
