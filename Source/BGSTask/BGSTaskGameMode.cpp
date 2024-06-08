// Copyright Epic Games, Inc. All Rights Reserved.

#include "BGSTaskGameMode.h"
#include "BGSTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

void ABGSTaskGameMode::LevelTimerFunction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("%f"), GetWorld()->TimeSeconds - LevelStartTime));
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("%f"), TotalScore));
	}

	if (GetWorld()->TimeSeconds >= LevelStartTime + LevelDurationSeconds)
	{
		GameStarted = false;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Yellow, FString::Printf(TEXT("Game Over")));
			GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Yellow, FString::Printf(TEXT("Final Score: %f"), TotalScore));
		}

		GetWorld()->GetTimerManager().ClearTimer(LevelTimerHandle);
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

	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Landed")));
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("%f (X%d)"), Score, JumpedActors.Num()));

		/*for (AActor* Obstacle : JumpedActors)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Obstacle->GetName());
		}*/
	}
}

void ABGSTaskGameMode::StartGame()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Game Start")));
	}

	TotalScore = 0.f;
	LevelStartTime = GetWorld()->TimeSeconds;
	
	GameStarted = true;

	GetWorld()->GetTimerManager().SetTimer(LevelTimerHandle, this, &ABGSTaskGameMode::LevelTimerFunction, 1.0f, true);
}
