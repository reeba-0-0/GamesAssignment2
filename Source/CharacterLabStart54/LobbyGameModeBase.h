// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERLABSTART54_API ALobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ALobbyGameModeBase();

	UFUNCTION()
	void MovePlayers();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	class AMyGameStateBase* gameStateRef;

private:
	int playerNum;
};
