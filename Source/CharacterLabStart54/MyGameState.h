// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERLABSTART54_API AMyGameState : public AGameState
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void TrackPlayerNum();

	UFUNCTION()
	int GetPlayerNum();

private:
	int playerNum = 0;
	
};
