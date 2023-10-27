// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthOrbContainer.h"

#include "HealthOrb.h"

FHealthOrbContainer::FHealthOrbContainer(AHealthOrb& HealthOrbToContain, AHealthPoint& OriginPoint): HealthOrb(
	                                                                                                     HealthOrbToContain), OrbOriginPoint(OriginPoint)
{
}

FHealthOrbContainer::~FHealthOrbContainer()
{
	UE_LOG(LogTemp, Warning, TEXT("Boop"));
	HealthOrb.Destroy();
}

AHealthOrb& FHealthOrbContainer::GetHealthOrb() const
{
	return HealthOrb;
}

AHealthPoint& FHealthOrbContainer::GetOrbOrigin() const
{
	return OrbOriginPoint;	
}
