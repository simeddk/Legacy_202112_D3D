// Copyright Epic Games, Inc. All Rights Reserved.

#include "U05_SynchronizationGameMode.h"
#include "U05_SynchronizationPawn.h"
#include "U05_SynchronizationHud.h"

AU05_SynchronizationGameMode::AU05_SynchronizationGameMode()
{
	DefaultPawnClass = AU05_SynchronizationPawn::StaticClass();
	HUDClass = AU05_SynchronizationHud::StaticClass();
}
