// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LearningMoreStuffGameMode.h"
#include "LearningMoreStuffPlayerController.h"
#include "LearningMoreStuffCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALearningMoreStuffGameMode::ALearningMoreStuffGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ALearningMoreStuffPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}