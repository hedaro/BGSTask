// Copyright Epic Games, Inc. All Rights Reserved.

#include "BGSTaskGameMode.h"
#include "BGSTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABGSTaskGameMode::ABGSTaskGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
