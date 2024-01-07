#pragma once

UENUM()
enum ETurretBuildErrors
{
	SocketOccupied,
	NotEnoughResources,
	NullUpgradePath,
	NullDataAsset,
	EmptyUpgradePath,
	NullPlayerReference,
	Success
};
