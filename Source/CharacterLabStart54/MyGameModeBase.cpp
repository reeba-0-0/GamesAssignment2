// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

void AMyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    gameStateRef = GetGameState<AMyGameState>();
    if (gameStateRef)
    {
        gameStateRef->IncrementPlayerCount();
    }
}
