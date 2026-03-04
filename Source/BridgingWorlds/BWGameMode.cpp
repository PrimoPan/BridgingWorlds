// Copyright Epic Games, Inc. All Rights Reserved.

#include "BWGameMode.h"

#include "BWObserverPawn.h"

ABWGameMode::ABWGameMode()
{
	DefaultPawnClass = ABWObserverPawn::StaticClass();
}
