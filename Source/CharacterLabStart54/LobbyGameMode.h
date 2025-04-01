// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERLABSTART54_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()
	
	UFUNCTION()
	void MovePlayers();

	class AMyGameStateBase* gameStateRef;

private:
	int playerNum;
};
