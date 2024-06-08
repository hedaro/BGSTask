// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BGSTaskGameMode.generated.h"

UCLASS(minimalapi)
class ABGSTaskGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UFUNCTION()
	void LevelTimerFunction();

	float LevelStartTime = 0.0;

	bool GameStarted = true;

	FTimerHandle LevelTimerHandle;

public:
	ABGSTaskGameMode();

	UFUNCTION(BlueprintCallable)
	void ProcessScore(const TArray<AActor*> &JumpedActors, float JumpTime);

	UFUNCTION(BlueprintCallable)
	void StartGame();

protected:
	UPROPERTY(BlueprintReadOnly)
	int TotalScore;

	UPROPERTY(EditDefaultsOnly)
	float ObstacleJumpValue = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float JumpTimeMultiplier = 1.2f;

	UPROPERTY(EditDefaultsOnly)
	float LevelDurationSeconds = 180.f;
};



