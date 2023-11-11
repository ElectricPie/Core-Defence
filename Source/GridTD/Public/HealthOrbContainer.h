// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AHealthPoint;
class AHealthOrb;
/**
 * 
 */
class GRIDTD_API FHealthOrbContainer
{
public:
	FHealthOrbContainer(AHealthOrb& HealthOrbToContain, AHealthPoint& OriginPoint);
	~FHealthOrbContainer();

	AHealthOrb& GetHealthOrb() const;
	AHealthPoint& GetOrbOrigin() const;

private:
	AHealthOrb& HealthOrb;
	AHealthPoint& OrbOriginPoint;
};
