// Copyright Epic Games, Inc. All Rights Reserved.

#include "U04_MultiPlayGameMode.h"
#include "U04_MultiPlayCharacter.h"
#include "UObject/ConstructorHelpers.h"

AU04_MultiPlayGameMode::AU04_MultiPlayGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
