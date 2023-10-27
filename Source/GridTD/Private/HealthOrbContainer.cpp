// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthOrbContainer.h"

FHealthOrbContainer::FHealthOrbContainer(AHealthOrb& HealthOrbToContain, AHealthPoint& OriginPoint): HealthOrb(
		HealthOrbToContain), OrbOriginPoint(OriginPoint)
{
}

FHealthOrbContainer::~FHealthOrbContainer()
{
}

AHealthOrb& FHealthOrbContainer::GetHealthOrb() const
{
	return HealthOrb;
}

AHealthPoint& FHealthOrbContainer::GetOrbOrigin() const
{
	return OrbOriginPoint;	
}
