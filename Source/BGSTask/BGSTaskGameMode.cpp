// Copyright Epic Games, Inc. All Rights Reserved.

#include "BGSTaskGameMode.h"
#include "BGSTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

void ABGSTaskGameMode::LevelTimerFunction()
{

	float RemainingTime = LevelStartTime + LevelDurationSeconds - GetWorld()->TimeSeconds;
	SetTime(RemainingTime);

	if (RemainingTime <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(LevelTimerHandle);
		
		GameStarted = false;
	}

}

ABGSTaskGameMode::ABGSTaskGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABGSTaskGameMode::ProcessScore(const TArray<AActor*> &JumpedActors, float JumpTime)
{
	float Score = JumpedActors.Num() * ObstacleJumpValue * JumpTime * JumpTimeMultiplier;
	TotalScore += Score;

	SetScore(TotalScore, JumpedActors.Num());
}

void ABGSTaskGameMode::StartGame()
{
	if (MainMenuWidgetClass)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		MainMenu = CreateWidget<UUserWidget>(PlayerController, MainMenuWidgetClass, TEXT("Main Menu"));
		MainMenu->AddToViewport();
	}

	TotalScore = 0.f;
	LevelStartTime = GetWorld()->TimeSeconds;
	SetTime(LevelStartTime);
	SetScore(TotalScore, 0);

	GameStarted = true;

	GetWorld()->GetTimerManager().SetTimer(LevelTimerHandle, this, &ABGSTaskGameMode::LevelTimerFunction, 1.0f, true);
}
