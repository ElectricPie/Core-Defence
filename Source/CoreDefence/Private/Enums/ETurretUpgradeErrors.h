#pragma once

UENUM()
enum ETurretUpgradeErrors
{
	TurretUpgradeNotEnoughResources,
	TurretUpgradeEndOfUpgradePath,
	TurretUpgradeNoTurretInSocket,
	TurretUpgradeNullUpgradePath,
	TurretUpgradeNullPlayerReference,
	TurretUpgradeNullDataAsset,
	TurretUpgradeSuccess
};
