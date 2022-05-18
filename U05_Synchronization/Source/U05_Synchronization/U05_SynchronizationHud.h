// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "U05_SynchronizationHud.generated.h"


UCLASS(config = Game)
class AU05_SynchronizationHud : public AHUD
{
	GENERATED_BODY()

public:
	AU05_SynchronizationHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
};
