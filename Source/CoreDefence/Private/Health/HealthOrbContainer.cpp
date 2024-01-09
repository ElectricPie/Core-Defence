// Fill out your copyright notice in the Description page of Project Settings.


#include "Health/HealthOrbContainer.h"

#include "Health/HealthOrb.h"

FHealthOrbContainer::FHealthOrbContainer(AHealthOrb& HealthOrbToContain, AHealthPoint& OriginPoint):
	HealthOrb(HealthOrbToContain), OrbOriginPoint(OriginPoint) {}

FHealthOrbContainer::~FHealthOrbContainer()
{
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

