#pragma once

UENUM()
enum ETurretBuildErrors
{
	TurretBuildSocketOccupied,
	TurretBuildNotEnoughResources,
	TurretBuildNullUpgradePath,
	TurretBuildNullDataAsset,
	TurretBuildEmptyUpgradePath,
	TurretBuildNullPlayerReference,
	TurretBuildSuccess
};
